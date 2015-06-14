#include <LedControl.h>
#include <math.h>

LedControl lc = LedControl(12,11,10,1);

int number = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
}

void loop() {
  // put your main code here, to run repeatedly:
//  lc.setDigit(0, 3, number, false);
//  if (number == 9) {
//     number = 0;
//  } else {
//    number++;
//  }
  printFloat(123);
  delay(1000);
}

void printFloat(float value) {
  int numDigits = log10(value) + 1;
  int whole = (int)value;
  Serial.print("number of digits: ");
  Serial.println(numDigits);
  Serial.print("whole number: ");
  Serial.println(whole);
  for (int i = 0; i < numDigits; i++) {
    int digit = whole % 10;
    whole = whole / 10;
    Serial.print("digit: ");
    Serial.println(digit);
    lc.setDigit(0, i, (byte)digit, false);  
  }    
}
