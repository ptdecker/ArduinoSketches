
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
  // put your setup code here, to run once:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  pinMode(inPin4, OUTPUT);
}

void loop() {
}
