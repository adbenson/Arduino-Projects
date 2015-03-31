#include "Arduino.h"
#include "FireMode.h"

FireMode::FireMode() {
  
        for (int i=0; i<NUMPIXELS; i++) {
          pixels[i] = 0; 
          
          levels[i] = 0; 
          goals[i] = 1;
        }

	rise = 0.05;
	fall = 0.02;
	dropoff = 0.25;
	minLevel = 0.15;
	choose = 120;

}

uint32_t * FireMode::step() {

  for(int i=0;i<NUMPIXELS;i++){
    double level = levels[i];

    if (level < goals[i]) {
      level = min(level + rise, 1);
    }
    else {
      goals[i] = 0;
      level = max(level - fall, minLevel);
    }

    //    Serial.println(levels[i]);
    int r = random(choose);
    if (r == 0) {// || (i >= 30 && i <= 31 && r < (choose/10))) {
      double goal = random(level * 1000, 1000) / 1000.0;
      goals[i] = 1;        
      pullAdjacent(i-1, 1); 
      pullAdjacent(i+1, 1); 
    }

    levels[i] = level;    

    pixels[i] = encodeColor(235 * level, 255 * level * level, 50 * level * level);

  }
  
  return pixels;

}

uint32_t FireMode::encodeColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void FireMode::pullAdjacent(int i, double pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  double level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
