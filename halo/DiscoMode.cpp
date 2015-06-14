#include "Arduino.h"
#include "DiscoMode.h"

void DiscoMode::step(Adafruit_NeoPixel* pixels) {
  
  if (discoState > 1024) {
    discoState = 0;
  }
  
  int offset = discoState / 1;
  
  int state = discoState / 4;
  
  int mode = discoState / 32;

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {
   
    int iOffset = ((offset / 32) %2 == 0)? i + offset : i - offset;
    
    int quad = quadrant(iOffset);
    
    color = hue((discoState / 128.0) * 255 + quad * (255.0 / 4.0));
    
    if (quad % 2 == state % 2) {
      color = 0;
    }
    
    pixels->setPixelColor(i, color);
  }

  discoState++;

}

int DiscoMode::quadrant(int i) {
   return (int)(((float)i / NUMPIXELS) * 4) % 4;
}
