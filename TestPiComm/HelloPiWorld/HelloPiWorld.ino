#define HWSERIAL Serial1

void setup() {
  HWSERIAL.begin(9600);
}

void loop() {
  HWSERIAL.println("Hello World!");
}
