void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < 1000; i++) {
    Serial.print("Line Number # [");
    Serial.print(i);
    Serial.println("]");
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
 
}
