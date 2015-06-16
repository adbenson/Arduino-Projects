#include "Arduino.h"
#include "FireMode.h"

void FireMode::step(Adafruit_NeoPixel* pixels) {

  for(int i=0;i<NUMPIXELS;i++){
    int level = levels[i];

    if (level < goals[i]) {
      //watch out for overflow!
      long newLevel = (long)level + rise;
      level = min(newLevel, MAX);
    }
    else {
      goals[i] = 0;
      level = max(level - fall, minLevel);
    }

    int r = random(choose);
    if (r == 0) {
      goals[i] = MAX;        
      pullAdjacent(i-1, MAX); 
      pullAdjacent(i+1, MAX); 
    }

    levels[i] = level;    

    float factor = (float)level / MAX;
    uint32_t color = rgb(235 * factor, 255 * factor * factor, 50 * factor * factor);
    pixels->setPixelColor(i, color);

  }
  
}

void FireMode::pullAdjacent(int i, int pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  int level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
