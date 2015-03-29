#ifndef HaloMode_h
#define HaloMode_h

#include "Arduino.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class HaloMode {
	public:
		HaloMode();
		
		uint32_t * step();

                static uint32_t encodeColor(uint8_t r, uint8_t g, uint8_t b);
                
	private:
		void pullAdjacent(int i, double pull);
	
                uint32_t pixels[NUMPIXELS];
                
		double levels [NUMPIXELS];
		double goals [NUMPIXELS];
		
		double rise;
		double fall;
		double dropoff;
		double minLevel;
		int choose;
};

#endif
