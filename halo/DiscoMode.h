#ifndef DiscoMode_h
#define DiscoMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class DiscoMode : public HaloMode {
	public:
		DiscoMode() : HaloMode() {
                   discoState = 0;
                };
		
		void step(Adafruit_NeoPixel* pixels);
	private:
                int discoState;
                
                int quadrant(int i);
};

#endif
