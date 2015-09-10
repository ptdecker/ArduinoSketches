#include <Morse.h>

const int ledPin = 13;

Morse morse(ledPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  morse.sendMorseString("SOS Todd");
}
