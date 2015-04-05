#include "Arduino.h"
#include "RainbowMode.h"

uint32_t * RainbowMode::step() {
  
  if (rainbowState >= 256*5) {
    rainbowState = 0; 
  }

  for(int i=0; i< NUMPIXELS; i++) {
    pixels[i] = hue(((i * 256 / NUMPIXELS) + rainbowState) & 255);
  }

  rainbowState++;
  
  return pixels;

}
