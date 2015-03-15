/*
 * SerialFormatting
 *
 * Print values in various formats to the serial port
 *
 */
 
char  chrValue   = 65;
byte  byteValue  = 65;
int   intValue   = 65;
float floatValue = 65.0;

void setup() {
  Serial.begin(9600);  
}

void loop() {

  Serial.print("chrValue: ");
  Serial.print(chrValue);
  Serial.print(" ");
  Serial.write(chrValue);
  Serial.print(" ");
  Serial.print(chrValue, DEC);
  Serial.println();


  Serial.print("byteValue: ");
  Serial.print(byteValue);
  Serial.print(" ");
  Serial.write(byteValue);
  Serial.print(" ");
  Serial.print(byteValue, DEC);
  Serial.println();

  Serial.print("intValue: ");
  Serial.print(intValue);
  Serial.print(" ");
  Serial.print(intValue, DEC);
  Serial.print(" ");
  Serial.print(intValue, HEX);
  Serial.print(" ");
  Serial.print(intValue, OCT);
  Serial.print(" ");
  Serial.print(intValue, BIN);
  Serial.println();

  Serial.print("floatValue: ");
  Serial.print(floatValue);
  Serial.println();


  delay(1000);
  
  chrValue++;
  byteValue++;
  intValue++;
  floatValue++;
  
}
