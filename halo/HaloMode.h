#ifndef HaloMode_h
#define HaloMode_h

#include "Arduino.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class HaloMode {
	public:
		HaloMode();
		
		virtual uint32_t * step() = 0;

                static uint32_t encodeColor(uint8_t r, uint8_t g, uint8_t b);
                
	protected:
                uint32_t pixels[NUMPIXELS];
};

#endif
