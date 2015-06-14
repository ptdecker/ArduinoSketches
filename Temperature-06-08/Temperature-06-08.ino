const int inPin = 0;
const int baudRate = 9600;

/**
 * Arduino setup event
 *
 * Called once upon Arduino reset
 */

void setup() {
  Serial.begin(baudRate);
  pinMode(13, OUTPUT);
}

/**
 * Arduino event loop
 *
 * Continuously looped
 */

void loop() {
  float celsius = getLM35Temp(inPin);
  logTemp(celsius);
  digitalWrite(13, HIGH); 
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

/**
 * The current temperature reading, in Celsius, from an LM35 compatible temperature sensor.
 *
 * @param inPin the Arduino analog pin to which the LM35 output is connected
 * @return      a floating point value of the current temperature in Celsius
 */

float getLM35Temp(int inPin) {
  int value = analogRead(inPin);
  float millivolts = (value / 1024.0) * 5000;
  float celsius = millivolts / 10;
  return celsius;
}

/**
 * Converts a floating point Celsius to Fahrenheit
 *
 * @param celsius the Celsius temperature value
 * @return        the Fahrenheit temperature value
 */

float celsiusToFahrenheit(float celsius) {
  float fahrenheit = (celsius * 9) / 5 + 32;
  return fahrenheit;
}

/**
 * Logs the current temperature to the serial port
 */
 
 void logTemp(float celsius) {
    Serial.print(celsius);
    Serial.print(" degrees Celsius, ");
    Serial.print(celsiusToFahrenheit(celsius));
    Serial.print(" degrees Fahrenheit");
    Serial.println();
}
