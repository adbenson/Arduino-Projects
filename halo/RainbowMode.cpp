#include "Arduino.h"
#include "RainbowMode.h"

void RainbowMode::step(Adafruit_NeoPixel* pixels) {
  
  if (rainbowState >= 256*5) {
    rainbowState = 0; 
  }

  for(int i=0; i< NUMPIXELS; i++) {
    uint32_t color = hue(((i * 256 / NUMPIXELS) + rainbowState) & 255);
    pixels->setPixelColor(i, color);
  }

  rainbowState++;

}
