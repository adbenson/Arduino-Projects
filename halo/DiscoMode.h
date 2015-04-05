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
		
		uint32_t * step();
	private:
                int discoState;
                
                int quadrant(int i);
};

#endif
