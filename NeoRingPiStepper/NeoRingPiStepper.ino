
#include <Adafruit_NeoPixel.h>

#define NEOPIN     17
#define NUMPIXELS  12
#define BRIGHTNESS 20
#define HWSERIAL   Serial1

// Define color patterns

#define COLOR_BLACK  0x000000
#define COLOR_RED    0xFF0000
#define COLOR_ORANGE 0xFF7F00
#define COLOR_YELLOW 0xFFFF00
#define COLOR_GREEN  0x00FF00
#define COLOR_BLUE   0x0000FF
#define COLOR_INDIGO 0x4B0082
#define COLOR_VIOLET 0xEE82EE
#define COLOR_PINK   0xFFCCCC
#define COLOR_WHITE  0xFFFFFF

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN);

int pos = 0;

void setup() {
  HWSERIAL.begin(9600);
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin();
  pos = 0;
}

void loop() {
  int incomingByte;
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    HWSERIAL.println();    
    HWSERIAL.print("Advanced to position: ");
    HWSERIAL.println(pos);
    pixels.setPixelColor(pos, COLOR_BLACK);
    pos++;
    if (pos == NUMPIXELS) 
      pos = 0;
    pixels.setPixelColor(pos, COLOR_WHITE);
    pixels.show();
  }
}
