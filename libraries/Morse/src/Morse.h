/*
 * Morse.h - Morse Code Universal Toolkit
 *
 * Based upon basic Morse code flasher by David A. Mellis, 2007-11-02 and
 * listed at https://www.arduino.cc/en/Hacking/LibraryTutorial
 */

#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse {
  public:
    Morse(int pin);
    void sendMorseString(String buffer);
  private:
    int _pin;
    void dot();
    void dash();
    void elementSpace();
    void charSpace();
    void wordSpace();
    void sendMorseChar(char buffer);
    void sendMorseWord(String buffer);
    String getNextWord(String buffer, int& bufferIndex);
};

#endif
