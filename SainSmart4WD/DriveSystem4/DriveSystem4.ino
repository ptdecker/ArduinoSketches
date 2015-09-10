
/* Test Drive System IV
 *
 * This version only provides forward throttle control with mode-reading filtering.
 *
 * Mode-reading filtering uses the mode value of the last ten readings from the receiver.
 *
 * Use #define DEGUG to send status information to serial port
 * Use #define SMOOTH to enable filtering. If not defined, raw translation is used
 
/*
 * Brushed motor control constants
 * Driven by L293 H-Bridge (via SainSmart L293 Driver Board)
 */

#define DEBUG
//#define SMOOTH
 
const int inPin1     = 6;  // Throttle receiver channel
const int outPin1    = 7;  // Left-side motors positive 
const int outPin2    = 8;  // Left-side motors negative
const int outPin3    = 9;  // Right-side motors positive
const int outPin4    = 10; // Right-side motors negative
const int enPinLeft  = 11; // Left-side motors enable pin
const int enPinRight = 12; // Right-side motors enable pin

const int minSpeed = 50;

int ch3 = 0;
int speed = 0;
int lastSpeed = 0;

#ifdef DEBUG
  int minCh3 = 9999;
  int maxCh3 = 0;
#endif

#ifdef SMOOTH
  const int buffSize = 10;
  int speedBuff[buffSize];
  int lastBuff = 0;
  int sumSpeed = 0;
  int avgSpeed = 0;
  int i;
#endif

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);
  pinMode(outPin3, OUTPUT);
  pinMode(outPin4, OUTPUT);
  pinMode(inPin1, INPUT);
  digitalWrite(outPin1, LOW);
  digitalWrite(outPin2, LOW);
  digitalWrite(outPin3, LOW);
  digitalWrite(outPin4, LOW);
  #ifdef SMOOTH
    for (i = 0; i < buffSize; i += 1) {
      speedBuff[i] = 0;
    }
  #endif
}

void loop() {

  ch3 = pulseIn(inPin1, HIGH);
  
  #ifdef SMOOTH
    if (ch3 < 1050) {
      ch3 = 1050;
    }
    speedBuff[lastBuff] = ch3;
    lastBuff = ((lastBuff += 1) > buffSize) ? 0 : lastBuff;
    sumSpeed = 0;
    for (i = 0; i < buffSize; i += 1) {
      sumSpeed += speedBuff[i];
    }
    ch3 = sumSpeed / buffSize;
  #endif
    
  speed = map(ch3, 1050, 1890, minSpeed, 255);
  
  if (speed < (minSpeed * 1.10)) {
    speed = 0;
  } else if (speed > 255) {
    speed = 255;
  }
  
  #ifdef DEBUG 
    minCh3 = (ch3 < minCh3) ? ch3 : minCh3;
    maxCh3 = (ch3 > maxCh3) ? ch3 : maxCh3;
  #endif
  
  if (speed != lastSpeed) {
    
    if (lastSpeed == 0) {
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, HIGH);
      digitalWrite(outPin3, HIGH);
      digitalWrite(outPin4, LOW);
      #ifdef DEBUG
        Serial.println("Forward");
      #endif
    }
  
    #ifdef DEBUG
      Serial.print(ch3);
      Serial.print(" ");
      Serial.print(speed);
      Serial.print(" ");
      Serial.print(minCh3);
      Serial.print(" ");
      Serial.print(maxCh3);
      Serial.println();
    #endif
  
    analogWrite(enPinLeft, speed);
    analogWrite(enPinRight, speed);
  
   if (speed == 0) {
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      digitalWrite(outPin3, LOW);
      digitalWrite(outPin4, LOW);
      #ifdef DEBUG
        Serial.println("Neutral");
      #endif
    }
  
    lastSpeed = speed;
  }
  
}
