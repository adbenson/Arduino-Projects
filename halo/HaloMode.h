#ifndef HaloMode_h
#define HaloMode_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class HaloMode {
	public:
		HaloMode();
		
		virtual void step(Adafruit_NeoPixel* pixels) = 0;

                static uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
                
                static uint32_t hue(byte hue);
};

#endif
