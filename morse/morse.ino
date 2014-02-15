/*
  Morse Code
*/
 
#include <string.h>

#define A_ASCII_START 65

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// Possible morse values
enum MorseValue {
  dot = 0,
  dash,
  charGap,
  wordGap,
  eleGap // Only used for time array
};

const int morseTimeUnit = 100;

// Time to pulse for each morse character
const int morseTimes[] = {
  morseTimeUnit, // dot
  morseTimeUnit * 3, // dash
  morseTimeUnit * 3, // charGap
  morseTimeUnit * 7, // wordGap
  morseTimeUnit // eleGap
};

// Character conversions for international morse code
char morseConversion[26][5] = {
  ".-", // A
  "-...", // B
  "-.-.", // C
  "-..", // D
  ".", // E
  "..-.", // F
  "--.", // G
  "....", // H
  "..", // I
  ".---", // J
  "-.-", // K
  ".-..", // L
  "--", // M
  "-.", // N
  "---", // O
  ".--.", // P
  "--.-", // Q
  ".-.", // R
  "...", // S
  "-", // T
  "..-", // U
  "...-", // V
  ".--", // W
  "-..-", // X
  "-.--", // Y
  "--.." // Z
};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  pulseString("SOS");
  //pulseMorseCode("... --- ...\t"); // Pulse SOS
  delay(2000);               // wait for a second
}

// Pulses a voltage level to led for the given duration in milliseconds
void pulse(int time, int voltage) {
  digitalWrite(led, voltage);
  delay(time);
}

// Pulse a morse code value to the led.
void pulseChar(int val) {
  // Keep track of whether last character was a dot or dash so we can pulse
  // an element gap delay if needed
  static bool lastCharWasElement = false; 
  
  MorseValue m = (MorseValue) val;
  
  if (m == dot || m == dash) {
    if (lastCharWasElement) // eleGap if needed
      pulse(morseTimes[eleGap], LOW);
    
    pulse(morseTimes[m], HIGH);
    lastCharWasElement = true;
  }
  else {
    pulse(morseTimes[m], LOW);
    lastCharWasElement = false;
  }
}

// Pulses a morse code string (... --- ...) to the led
void pulseMorseCode(char* morse) {
  int strLen = strlen(morse);
  for (int i = 0; i < strLen; i++) {
    switch(morse[i]) {
      case '.':
        pulseChar(dot);
        break;
      case '-':
        pulseChar(dash);
        break;
      case ' ':
        pulseChar(charGap);
        break;
      case '\t':
        pulseChar(wordGap);
        break;
      default:
        printf("Error: Bad character in morse string: %c\n", morse[i]);
    }
  }
}

// Pulses an ascii string to the led in morse code
void pulseString(char* source) {
  int strLen = strlen(source);
  for (int i = 0; i < strLen; i++) {

    if (isalpha(source[i])) {
      // make sure it's upper because that's how table is calculated
      int val = toupper(source[i]) - A_ASCII_START;
      pulseMorseCode(morseConversion[val]);
      pulseChar(charGap);
    }
    else if (source[i] == ' ') {
      pulseChar(wordGap);
    }
    else {
      printf("Error:  Cannot convert %c to morse code.\n", source[i]);
    }

  }
}
