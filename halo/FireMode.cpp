#include "Arduino.h"
#include "FireMode.h"

void FireMode::step(Adafruit_NeoPixel* pixels) {

  for(int i=0;i<NUMPIXELS;i++){
    double level = levels[i];

    if (level < goals[i]) {
      level = min(level + rise, 1);
    }
    else {
      goals[i] = 0;
      level = max(level - fall, minLevel);
    }

    int r = random(choose);
      goals[i] = 1;        
      pullAdjacent(i-1, 1); 
      pullAdjacent(i+1, 1); 
    }

    levels[i] = level;    

    uint32_t color = rgb(235 * level, 255 * level * level, 50 * level * level);
    pixels->setPixelColor(i, color);

  }
  
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
