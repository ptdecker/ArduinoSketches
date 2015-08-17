
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
const int minSpeed   = 50;

const int NEUTRAL = 0;
const int FORWARD = 1;
const int REVERSE = 2;
const int CW      = 3;
const int CCW     = 4;


int speed = 0;
int directionMode = NEUTRAL;

void emergency() {
      analogWrite(enPinLeft, 0);
      analogWrite(enPinRight, 0);
      digitalWrite(inPin1, LOW);
      digitalWrite(inPin2, LOW);
      digitalWrite(inPin3, LOW);
      digitalWrite(inPin4, LOW);
      speed = 0;
      directionMode = NEUTRAL;
}

void stop() {
      setSpeed(0);
}

void setSpeed(int newSpeed) {
  int rate = 100 / abs(newSpeed - speed);
  if ((speed == 0) && (newSpeed > minSpeed)) {
    speed = minSpeed;
  }
  while (abs(newSpeed - speed) > 0) {
      if (newSpeed > speed) {
        speed += 1;
      } else {
        speed -= 1;
      }
      if ((speed < minSpeed) && (newSpeed == 0)) {
        speed = 0;
      }
      analogWrite(enPinLeft, speed);
      analogWrite(enPinRight, speed);
      delay(rate);
  }
}

void setDirection(int newDirection) {
  int oldSpeed = 0;
  switch(newDirection) {
    case NEUTRAL:
      setSpeed(0);
      digitalWrite(inPin1, LOW);
      digitalWrite(inPin2, LOW);
      digitalWrite(inPin3, LOW);
      digitalWrite(inPin4, LOW);
      directionMode = newDirection;
      break;
    case FORWARD:
      if (directionMode == REVERSE) {
        oldSpeed = speed;
        setSpeed(0);
      }
      digitalWrite(inPin1, LOW);
      digitalWrite(inPin2, HIGH);
      digitalWrite(inPin3, HIGH);
      digitalWrite(inPin4, LOW);
      if (directionMode == REVERSE) {
        setSpeed(oldSpeed);
      }
      directionMode = newDirection;
      break;
    case REVERSE:
      if (directionMode == FORWARD) {
        oldSpeed = speed;
        setSpeed(0);
      }
      digitalWrite(inPin1, HIGH);
      digitalWrite(inPin2, LOW);
      digitalWrite(inPin3, LOW);
      digitalWrite(inPin4, HIGH);
      if (directionMode == FORWARD) {
          setSpeed(oldSpeed);
      }
      directionMode = newDirection;
      break;
    case CW:
      if (directionMode != NEUTRAL) {
        Serial.println("Must be in neutral before clockwise rotation is possible");
        break;
      }
      digitalWrite(inPin1, LOW);
      digitalWrite(inPin2, HIGH);
      digitalWrite(inPin3, LOW);
      digitalWrite(inPin4, HIGH);
      directionMode = newDirection;
      break;
    case CCW:
      if (directionMode != NEUTRAL) {
        Serial.println("Must be in neutral before counter-clockwise rotation is possible");
        break;
      }
      digitalWrite(inPin1, HIGH);
      digitalWrite(inPin2, LOW);
      digitalWrite(inPin3, HIGH);
      digitalWrite(inPin4, LOW);
      directionMode = newDirection;
      break;
    default:
      Serial.print("Invalid direction mode: '");
      Serial.print(directionMode);
      Serial.print("'");
      Serial.println();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(inPin3, OUTPUT);
  pinMode(inPin4, OUTPUT);
  Serial.println("'0' through '9' to set speed, 'f', 'r', 'c', 'x' to set direction. 'N' for netural. 'e' for emergency.");
  setDirection(NEUTRAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'E' || ch == 'e') {
      emergency();
      Serial.println("Emergency Stop (Speed = 0, Neutral)");
    } else if (isDigit(ch) && ch == '0') {
      stop();
      Serial.println("Stopped");
    } else if (isDigit(ch)) {
      if (directionMode == NEUTRAL) {
        Serial.println("Unable to start--current in neutral.");
      } else {
        setSpeed(map(ch, '0', '9', minSpeed, 255));
        Serial.print("Speed ");
        Serial.print(speed);
        Serial.println();
      }
    } else if (ch == 'F' || ch == 'f') {
      setDirection(FORWARD);
      Serial.println("Forward");
    } else if (ch == 'R' || ch == 'r') {
      setDirection(REVERSE);
      Serial.println("Reverse");
    } else if (ch == 'N' || ch == 'n') {
      setDirection(NEUTRAL);
      Serial.println("Netural");
    } else if (ch == 'C' || ch == 'c') {
      setDirection(CW);
      Serial.println("Clockwise");
    } else if (ch == 'X' || ch == 'x') {
      setDirection(CCW);
      Serial.println("Counter-clockwise");
    } else {
      Serial.print("Unexpected command: '");
      Serial.print(ch);
      Serial.print("'!");
      Serial.println();
    }
  }
}
