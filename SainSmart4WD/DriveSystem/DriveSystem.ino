
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
const int minSpeed   = 50;

const int inPin1 = 7;

const int NEUTRAL = 0;
const int FORWARD = 1;
const int REVERSE = 2;
const int CW      = 3;
const int CCW     = 4;


int ch3 = 0;
int speed = 0;
int adjSpeed = 0;
int oldSpeed = 0;
int directionMode = NEUTRAL;
int speeds[5] = {0, 0, 0, 0, 0};
int lastSpeedIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);
  pinMode(outPin3, OUTPUT);
  pinMode(outPin4, OUTPUT);
  pinMode(inPin1, INPUT);
}

void loop() {

  speeds[lastSpeedIndex] = pulseIn(inPin1, HIGH, 25000);
  lastSpeedIndex = (lastSpeedIndex == 4) ? 0 : (lastSpeedIndex += 1);
  ch3 = (speeds[0] + speeds[1] + speeds[2] + speeds[3] + speeds[4]) / 5;

  speed = map(ch3, 1050, 1859, -10, 10);
  if (speed > 10) {
    speed = 10;
  } else if (speed < -10) {
    speed = -10;
  }
    
  adjSpeed = map(abs(speed), 1, 10, minSpeed, 255);
  
  if ((oldSpeed != 0) && (speed == 0)) {
    Serial.println("Neutral");
    digitalWrite(outPin1, LOW);
    digitalWrite(outPin2, LOW);
    digitalWrite(outPin3, LOW);
    digitalWrite(outPin4, LOW);
    Serial.println("Neutral");
  } else if ((oldSpeed <= 0) && (speed > 0)) {
    digitalWrite(outPin1, LOW);
    digitalWrite(outPin2, HIGH);
    digitalWrite(outPin3, HIGH);
    digitalWrite(outPin4, LOW);
    Serial.println("Forward");
  } else if ((oldSpeed >= 0) && (speed < 0)) {
    digitalWrite(outPin1, HIGH);
    digitalWrite(outPin2, LOW);
    digitalWrite(outPin3, LOW);
    digitalWrite(outPin4, HIGH);
    Serial.println("Reverse");
  }    
    
  
  if (speed > 0) {
    analogWrite(enPinLeft, adjSpeed);
    analogWrite(enPinRight, adjSpeed);
//    Serial.print("Forward: ");
//    Serial.print(speed);
//    Serial.print(" (");
//    Serial.print(adjSpeed);
//    Serial.println(")");    
  } else if (speed < 0) {
    analogWrite(enPinLeft, adjSpeed);
    analogWrite(enPinRight, adjSpeed);
//    Serial.print("Reverse: ");
//    Serial.print(abs(speed));
//    Serial.print(" (");
//    Serial.print(adjSpeed);
//    Serial.println(")");

  }
  
  delay(200);
  oldSpeed = speed;
  
}
