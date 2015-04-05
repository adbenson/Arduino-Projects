#include "Arduino.h"
#include "HaloMode.h"

uint32_t HaloMode::pixels[NUMPIXELS];

HaloMode::HaloMode() {
  
        for (int i=0; i<NUMPIXELS; i++) {
          pixels[i] = 0; 
        }
}

uint32_t HaloMode::rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t HaloMode::hue(byte hue) {
  hue = 255 - hue;
  
  if (hue < 85) {
    return rgb(255 - hue * 3, 0, hue * 3);
  } else if (hue < 170) {
    hue -= 85;
    return rgb(0, hue * 3, 255 - hue * 3);
  } else {
    hue -= 170;
    return rgb(hue * 3, 255 - hue * 3, 0);
  }
}

