#ifndef FireWaveMode_h
#define FireWaveMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1
#define MAX            32767

class FireWaveMode : public HaloMode {
	public:
		FireWaveMode() : HaloMode() {
  
                        for (int i=0; i<NUMPIXELS; i++) {
                          levels[i] = 0; 
                          goals[i] = MAX;
                        }
                
                	rise = 0.10 * MAX;
                	fall = 0.04 * MAX;
                	dropoff = 0.1 * MAX;
                	minLevel = 0.15 * MAX;
                	choose = 500;

                };
		
		void step(Adafruit_NeoPixel* pixels);
	private:
		void pullAdjacent(int i, int pull);
                
		int levels [NUMPIXELS];
		int goals [NUMPIXELS];
		
		int rise;
		int fall;
		int dropoff;
		int minLevel;
		int choose;
};

#endif
