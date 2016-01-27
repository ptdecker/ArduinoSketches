
#include <Adafruit_NeoPixel.h>

#define PIN 17

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  mode      = 0;        // Current animation effect
uint8_t  offset    = 0;        // Position of spinny eyes
uint32_t color     = 0xff0095; // Start red
uint32_t prevTime;

void setup() {
    pixels.begin();
    pixels.setBrightness(20);   // 1/3 brightness
    prevTime = millis();
}

void loop() {
   
    uint32_t standardDelay = 1500;
    uint32_t shortDelay    = 750;

    rainbowMode();
    rainbowMode();
  
    for (uint32_t loopCount =0; loopCount < 1; loopCount++) {
        loopRoundOnce(1);
        resetRing();
        pulse(1);
        resetRing();
        delay(standardDelay);
    }
    
    loopRoundOnce(2);
    resetRing();
    pulse(2);
    resetRing();
    delay(standardDelay);
    
    for (uint32_t loopCount =0; loopCount < 1; loopCount++) {
        loopRoundOnce(1);
        resetRing();
        pulse(1);
        resetRing();
        delay(standardDelay);
   }
 
   loopRoundOnce(2);
   resetRing();
   pulse(2);
   resetRing();
   delay(shortDelay);

   rainbowMode();
   delay(shortDelay);
   rainbowMode();
   delay(shortDelay);
   rainbowMode();
   delay(shortDelay);

}

void endSequence() {
    while(1) {
        delay(10000);
    } 
}

void rainbowMode() {

    // Place on 5 lights at a time, each new light lit will be a from an index of a rainbow array

    uint32_t color[] = {
        0xff0000,
        0xff7f00,
        0xffff00,
        0x00ff00, 
        0x0000ff, 
        0x4b0082, 
        0x8f00ff
    };

    for(uint32_t i=0; i<24; i++) {
      
        // The current pixel is always the same colour
        // It's the last X colours which are different

        pixels.setPixelColor(i, color[0]);       

        if (i>0) {
          pixels.setPixelColor(i-1, color[1]);       
        }

        if (i>1) {
          pixels.setPixelColor(i-2, color[2]);       
        }

        if (i>2) {
            pixels.setPixelColor(i-3, color[3]);       
        }

        if (i>3) {
            pixels.setPixelColor(i-4, color[4]);       
        }

        if (i>4) {
            pixels.setPixelColor(i-5, color[5]);       
        }

        pixels.setPixelColor(i-6, 0);
        pixels.show(); 
        delay(100); 
    }

    // Then hide the last 3 in reverse order
    pixels.setPixelColor(18, 0);    
    pixels.show(); 
    delay(100);  
    pixels.setPixelColor(19, 0);    
    pixels.show(); 
    delay(100);  
    pixels.setPixelColor(20, 0);    
    pixels.show(); 
    delay(100);  
    pixels.setPixelColor(21, 0);    
    pixels.show(); 
    delay(100);    
    pixels.setPixelColor(22, 0);       
    pixels.show(); 
    delay(100); 
    pixels.setPixelColor(23, 0);       
    pixels.show(); 
    delay(100); 

}

void pulse(uint32_t colorGood) {
  
    if (colorGood == 1) {
      
        // Up
        for (uint32_t b=0; b<30; b++) {
            for(uint32_t i=0; i<24; i++) {
                pixels.setPixelColor(i, 0xffffff);
                pixels.setBrightness(b);
            }
            pixels.show();
            delay(50);   
        }

        // down
        for (uint32_t d=30; d>0; d--) {
            for(uint32_t j=0; j<24; j++) {
                pixels.setPixelColor(j, 0xffffff);   
                pixels.setBrightness(d);
            }
            pixels.show();
            delay(50);   
        }

        for(uint32_t i=0; i<24; i++) {
            pixels.setPixelColor(i, 0);   
            pixels.setBrightness(0);
            pixels.show();
        }
        
    } else {
      
       // Up
       for (uint32_t b=0; b<30; b++) {
            for(uint32_t i=0; i<24; i++) {
                pixels.setPixelColor(i, 0xff0000);
                pixels.setBrightness(b);
            }
            pixels.show();
            delay(50);   
        }

        // down
        for (uint32_t d=30; d>0; d--) {
            for(uint32_t j=0; j<24; j++) {
                pixels.setPixelColor(j, 0xff0000);   
                pixels.setBrightness(d);
            }
            pixels.show();
            delay(50);   
        }

        // reset
        for(uint32_t i=0; i<24; i++) {
            pixels.setPixelColor(i, 0);   
            pixels.setBrightness(0);
            pixels.show();
        }
    }
}

void resetRing() {
    for(uint32_t i=0; i<24; i++) {
        pixels.setPixelColor(i, 0);   
        pixels.setBrightness(30);
    }
    pixels.show();
}

void loopRoundOnce(uint32_t colorGood) {
    if (colorGood == 1) {
        for(uint32_t i=0; i<24; i++) {
            if (i>0) {
                pixels.setPixelColor((i-1), 0);     
            }
            pixels.setPixelColor(i, 0xffffff);       
            pixels.show(); 
            delay(100); 
        }
        for(uint32_t i=0; i<24; i++) {
            pixels.setPixelColor(i, 0);   
        }  
        pixels.show() 
    } else {
        for(uint32_t i=0; i<24; i++) {
            if (i>0) {
                pixels.setPixelColor((i-1), 0);     
            }
            pixels.setPixelColor(i, 0xff0000);       
            pixels.show(); 
            delay(100); 
        }
        for(uint32_t i=0; i<24; i++) {
            pixels.setPixelColor(i, 0);   
        }  
        pixels.show();
    } 
}
