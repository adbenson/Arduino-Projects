#ifndef ChaseMode_h
#define ChaseMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class ChaseMode : public HaloMode {
	public:
		ChaseMode() : HaloMode() {
                   chaseState = 0;
                };
		
		void step(Adafruit_NeoPixel* pixels);
	private:
                int chaseState;
};

#endif
