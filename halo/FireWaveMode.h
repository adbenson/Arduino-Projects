#ifndef FireWaveMode_h
#define FireWaveMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class FireWaveMode : public HaloMode {
	public:
		FireWaveMode() : HaloMode() {
  
                        for (int i=0; i<NUMPIXELS; i++) {
                          levels[i] = 0; 
                          goals[i] = 1;
                        }
                
                	rise = 0.10;
                	fall = 0.04;
                	dropoff = 0.1;
                	minLevel = 0.15;
                	choose = 500;

                };
		
		void step(Adafruit_NeoPixel* pixels);
	private:
		void pullAdjacent(int i, double pull);
                
		float levels [NUMPIXELS];
		float goals [NUMPIXELS];
		
		double rise;
		double fall;
		double dropoff;
		double minLevel;
		int choose;
};

#endif
