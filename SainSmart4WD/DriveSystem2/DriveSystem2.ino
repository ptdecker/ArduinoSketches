
/*
 * Brushed motor control constants
 * Driven by L293 H-Bridge (via SainSmart L293 Driver Board)
 */
 
const int enPinLeft  = 12; // Left-side motors enable pin
const int enPinRight = 13; // Right-side motors enable pin
const int outPin1     =  8; 
const int outPin2     =  9;
const int outPin3     = 10;
const int outPin4     = 11;

const int inPin1 = 7;

const int minSpeed = 50;

int ch3 = 0;
int speed = 0;
int oldSpeed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);
  pinMode(outPin3, OUTPUT);
  pinMode(outPin4, OUTPUT);
  pinMode(inPin1, INPUT);
}

void loop() {

  ch3 = pulseIn(inPin1, HIGH);
  
  speed = map(ch3, 1050, 1859, minSpeed, 255);
  
  if (speed < (minSpeed * 1.10)) {
    speed = 0;
  } else if (speed > 255) {
    speed = 255;
  }

  if (speed == 0) {
    digitalWrite(outPin1, LOW);
    digitalWrite(outPin2, LOW);
    digitalWrite(outPin3, LOW);
    digitalWrite(outPin4, LOW);
  } else if ((oldSpeed == 0) && (speed > 0)) {
    digitalWrite(outPin1, LOW);
    digitalWrite(outPin2, HIGH);
    digitalWrite(outPin3, HIGH);
    digitalWrite(outPin4, LOW);
  }    
    
  
  if (speed > 0) {
    analogWrite(enPinLeft, speed);
    analogWrite(enPinRight, speed);
  }
  
  oldSpeed = speed;
  
}
