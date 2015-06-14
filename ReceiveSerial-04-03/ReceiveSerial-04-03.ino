const int ledPin    = 13;
const int baudRate  = 9600;
      int blinkRate = 0;

void setup() {
  Serial.begin(baudRate);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (isDigit(ch)) {
      blinkRate = (ch - '0');
      blinkRate = blinkRate * 100;
    }
    Serial.print("Blinking rate set to ");
    Serial.print(blinkRate);
    Serial.println(" ms");
  }
  blink();
}

void blink() {
  if (blinkRate > 0) {
    digitalWrite(ledPin, HIGH);
    delay(blinkRate);
  }
  digitalWrite(ledPin, LOW);
  delay(blinkRate);
}
