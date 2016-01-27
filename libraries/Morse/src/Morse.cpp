/*
 * Morse.cpp - Morse Code Universal Toolkit
 *
 * Based upon basic Morse code flasher by David A. Mellis, 2007-11-02 and
 * listed at https://www.arduino.cc/en/Hacking/LibraryTutorial.  Also, help
 * from the following sources:
 *
 *    - http://stackoverflow.com/questions/24500826/how-to-create-conversion-lookup-table-with-variable-string-length-in-c
 *    - http://embeddedgurus.com/stack-overflow/2010/01/a-tutorial-on-lookup-tables-in-c/
 *    - http://forum.arduino.cc/index.php?topic=58289.0 (snarky comments aside)
 *    - http://forum.arduino.cc/index.php?topic=191396.0 (plus somemore snark to ignore)
 *    - 
 */

/*
 * TODO: numbers
 * TODO: symbols
 * TODO: sound
 * TODO: specials
 * TODO: dynamic word speed
 * TODO: decoding
 */

#include "Arduino.h"
#include "Morse.h"

/*
 * Spacing constants
 */

#define DOT_LEN       100 // The dash length determines the other lengths
#define DASH_LEN      300 // 3x DOT_LEN is the dot length
#define ELEMENT_SPACE 100 // 1x DOT_LEN is the space between dots and dashes
#define CHAR_SPACE    300 // 3x DOT_LEN is the space between characters
#define WORD_SPACE    700 // 7x DOT_LEN is the space between words

#define DOT_CHAR       '.'
#define WORD_DELIMITER ' '

/*
 * Morse code lookup tables
 */

static const String morseAlpha[26] = {
  ".-",    // [ 0] = A 
  "-...",  // [ 1] = B
  "-.-.",  // [ 2] = C
  "-..",   // [ 3] = D
  ".",     // [ 4] = E
  "..-.",  // [ 5] = F
  "--.",   // [ 6] = G
  "....",  // [ 7] = H
  "..",    // [ 8] = I
  ".---",  // [ 9] = J
  "-.-",   // [10] = K
  ".-..",  // [11] = L
  "--",    // [12] = M
  "-.",    // [13] = N
  "---",   // [14] = O
  ".--.",  // [15] = P
  "--.-",  // [16] = Q
  ".-.",   // [17] = R
  "...",   // [18] = S
  "-",     // [19] = T
  "..-",   // [20] = U
  "...-",  // [21] = V
  ".--",   // [22] = W
  "-..-",  // [23] = X
  "-.--",  // [24] = Y
  "--.."   // [25] = Z
};

static const String morseDigits[10] = {
  "-----",  // [0] = 0
  ".----",  // [1] = 1
  "..---",  // [2] = 2
  "...--",  // [3] = 3
  "....-",  // [4] = 4
  ".....",  // [5] = 5
  "-....",  // [6] = 6
  "--...",  // [7] = 7
  "---..",  // [8] = 8
  "----."   // [9] = 9
};

static const String morseSymbols[18] = {
  ".-.-.-",   // [ 0] = '.'
  "--..--",   // [ 1] = ','
  "..--..",   // [ 2] = '?'
  ".----.",   // [ 3] = '''
  "-.-.--",   // [ 4] = '!'
  "-..-.",    // [ 5] = '/'
  "-.--.",    // [ 6] = '('
  "-.--.-",   // [ 7] = ')'
  ".-...",    // [ 8] = '&'
  "---...",   // [ 9] = ':'
  "-.-.-.",   // [10] = ';'
  "-...-",    // [11] = '='
  ".-.-.",    // [12] = '+'
  "-....-",   // [13] = '-'
  "..--.-",   // [14] = '_'
  ".-..-.",   // [15] = '\'
  "...-..-",  // [16] = '$'
  ".--.-."    // [17] = '@'
};

/*
 * Constructor
 */
 
 Morse::Morse(int pin) {
   pinMode(pin, OUTPUT);
   _pin = pin;
 }
 
/*
 * Send a 'dot' to the LED pin
 */
 
void Morse::dot() {
  digitalWrite(_pin, HIGH);
  delay(DOT_LEN);
  digitalWrite(_pin, LOW);
}

/*
 * Send a 'dash' to the LED pin
 */

void Morse::dash() {
  digitalWrite(_pin, HIGH);
  delay(DASH_LEN);
  digitalWrite(_pin, LOW);
} 

/*
 * Delay the standard element space
 */

 void Morse::elementSpace() {
  delay(ELEMENT_SPACE);
 }

 /*
 * Delay the standard character space
 */

void Morse::charSpace() {
  delay(CHAR_SPACE);
 }

 /*
 * Delay the standard word space
 */

 void Morse::wordSpace() {
  delay(WORD_SPACE);
 }

 /*
  * Send a morse code character
  *
  * Look up the dot-dash elements for the passed character. Then loop through all the elements in
  * turn. Between elements add proper element spacing.
  */

void Morse::sendMorseChar(char buffer) {
  String morseString = morseAlpha[(int)buffer - (int)'A'];
  for (int morseStringCharIndex = 0; morseStringCharIndex < morseString.length(); morseStringCharIndex++) {
    if (morseStringCharIndex != 0) elementSpace();
    if (morseString.charAt(morseStringCharIndex) == DOT_CHAR)
      dot();
    else
      dash();
  }    
}

 /*
  * Send a morse code word
  *
  * Loop through all the characters in a word sending each character in turn. Between characters
  * add proper character spacing. And, add a word space at the end.
  */

void Morse::sendMorseWord(String buffer) {
  Serial.println("Sending " + buffer);
  for (int bufferIndex = 0; bufferIndex < buffer.length(); bufferIndex++) {
    if (bufferIndex != 0) charSpace();
    sendMorseChar(buffer.charAt(bufferIndex));
  }
}

/*
 * getNextWord helper function 
 */

String Morse::getNextWord(String buffer, int& bufferIndex) {
  String nextWord = "";
  while (bufferIndex < buffer.length() && buffer.charAt(bufferIndex) != WORD_DELIMITER) {
    nextWord = nextWord + buffer.charAt(bufferIndex);
    bufferIndex++;
  }
//  if (bufferIndex < buffer.length() && buffer.charAt(bufferIndex) == WORD_DELIMITER) bufferIndex++;
  return nextWord;
}

/*
 * Send a morse code String
 *
 * Loop through all the words in a string using WORD_DELIMITER to indicate the breaks between
 * words. Between words, add proper word spacing. 
 */

void Morse::sendMorseString(String buffer) {
  buffer.toUpperCase();
  for (int bufferIndex = 0; bufferIndex < buffer.length(); bufferIndex++) {
    if (bufferIndex != 0) wordSpace();
    sendMorseWord(getNextWord(buffer, bufferIndex));
  }
}