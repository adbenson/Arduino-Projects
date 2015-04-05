#include "Arduino.h"
#include "DiscoMode.h"

uint32_t * DiscoMode::step() {
  
  if (discoState > 10) {
    discoState = 0;
  }

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {   
    if ((quadrant(i) % 2) != (discoState / 5)) {
      int n = (i + discoState) % 255;
      color = rgb(255 - n, n, 255);
    }
    else {
      color = 0;  
    }
    
    pixels[i] = color;
  }

  discoState++;
  
  return pixels;

}

int DiscoMode::quadrant(int i) {
   return (i / NUMPIXELS) / 4;
}
