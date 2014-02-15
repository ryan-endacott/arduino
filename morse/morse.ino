/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#include <string.h>


// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

enum MorseValue {
  dot = 0,
  dash,
  charGap,
  wordGap,
  eleGap // Only used for time array
};

const int morseTimeUnit = 100;

const int morseTimes[] = {
  morseTimeUnit, // dot
  morseTimeUnit * 3, // dash
  morseTimeUnit * 3, // charGap
  morseTimeUnit * 7, // wordGap
  morseTimeUnit // eleGap
};

/*
const int dotTime = morseTimeUnit;
const int dashTime = morseTimeUnit * 3;
const int elementGapTime = morseTimeUnit;
const int charGapTime = morseTimeUnit * 3;
const int wordGapTime = morseTimeUnit * 7;
*/

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  pulseMorseCode("... --- ...\t"); // Pulse SOS
  delay(2000);               // wait for a second
}

// pulses a voltage level for the given duration in milliseconds
void pulse(int time, int voltage) {
  digitalWrite(led, voltage);
  delay(time);
}

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
        printf("Error: Bad character in morse string: %c", morse[i]);
    }
  }
}
