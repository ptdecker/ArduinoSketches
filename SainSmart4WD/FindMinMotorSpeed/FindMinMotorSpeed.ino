
/*
 * Brushed motor control constants
 * Driven by L293 H-Bridge (via SainSmart L293 Driver Board)
 */
 
const int enPinLeft  = 12; // Left-side motors enable pin
const int enPinRight = 13; // Right-side motors enable pin
const int inPin1     =  8; 
const int inPin2     =  9;
const int inPin3     = 10;
const int inPin4     = 11;

void setup() {
  Serial.begin(9600);
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  pinMode(inPin4, OUTPUT);
  digitalWrite(inPin1, HIGH);
  digitalWrite(inPin2, LOW);
}

void loop() {
  analogWrite(enPinLeft, 0);
  Serial.println("Stopped, waiting five seconds to start...");
  delay(5000);
  Serial.println("Speeding up...");
  for (int speed = 40; speed < 60; speed += 1) {
    analogWrite(enPinLeft, speed);
    Serial.print("Speed now set at ");
    Serial.print(speed);
    Serial.print(" for one second");
    Serial.println();
    delay(1000);
  }
  Serial.println("Slowing down...");
  for (int speed = 59; speed > 35; speed -= 1) {
    analogWrite(enPinLeft, speed);
    Serial.print("Speed now set at ");
    Serial.print(speed);
    Serial.print(" for one second");
    Serial.println();
    delay(1000);
  }  
  Serial.println("Stopping");
  analogWrite(enPinLeft, 0);
  Serial.println("Waiting five seconds for full stop...");
  delay(5000);
}
