#ifndef FireMode_h
#define FireMode_h

#include "Arduino.h"
#include "HaloMode.h"

#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

class FireMode : public HaloMode {
	public:
		FireMode() : HaloMode() {
  
                        for (int i=0; i<NUMPIXELS; i++) {
                          levels[i] = 0; 
                          goals[i] = 1;
                        }
                
                	rise = 0.05;
                	fall = 0.02;
                	dropoff = 0.25;
                	minLevel = 0.15;
                	choose = 120;

                };
		
		uint32_t * step();
	private:
		void pullAdjacent(int i, double pull);
                
		double levels [NUMPIXELS];
		double goals [NUMPIXELS];
		
		double rise;
		double fall;
		double dropoff;
		double minLevel;
		int choose;
};

#endif
