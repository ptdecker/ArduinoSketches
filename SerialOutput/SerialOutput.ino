/*
 * SerialOutput
 *
 * Prints numbers to the serial port
 *
 */

int number = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("The number is ");
  Serial.println(number);
  delay(500);
  number++;
}
