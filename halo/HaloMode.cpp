#include "Arduino.h"
#include "HaloMode.h"

HaloMode::HaloMode() {
  
        for (int i=0; i<NUMPIXELS; i++) {
          pixels[i] = 0; 
        }
}

uint32_t HaloMode::encodeColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}


