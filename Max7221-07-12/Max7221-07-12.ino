#include <SPI.h>

const int slaveSelect = 10;
const int numberOfDigits = 4;
const int maxCount = 9999;

int number = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(slaveSelect, LOW);
  digitalWrite(slaveSelect, LOW);
  sendCommand(12, 1);
  sendCommand(15, 0);
  sendCommand(10, 8);
  sendCommand(11, numberOfDigits);
  sendCommand(9, 255);
  digitalWrite(slaveSelect, HIGH);
}

void loop() {
//  sendCommand(1, 1);
//  delay(1000);
//      displayNumber(number);
//      number = number + 1;
//      if (number > maxCount) {
//        number = 0;
//      }
//      delay(1000);
}

void displayNumber(int number) {
  for (int i = 0; i < numberOfDigits; i++) {
    byte character = number % 10;
    if (number == 0 && i > 0) {
      character = 0xf;
    }
    sendCommand(numberOfDigits - i, character);
    number = number / 10;
  }
}

void sendCommand(int command, int value) {
  Serial.print(">send command '");
  Serial.print(command);
  Serial.print("', value '");
  Serial.print(value);
  Serial.println("'");
  digitalWrite(slaveSelect, LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(slaveSelect, HIGH);
}

