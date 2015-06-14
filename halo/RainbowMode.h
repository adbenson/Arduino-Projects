#ifndef RainbowMode_h
#define RainbowMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class RainbowMode : public HaloMode {
	public:
		RainbowMode() : HaloMode() {
                   rainbowState = 0;
                };
		
		void step(Adafruit_NeoPixel* pixels);
	private:
                int rainbowState;
};

#endif
