#include "Arduino.h"
#include "FireWaveMode.h"

void FireWaveMode::step(Adafruit_NeoPixel* pixels) {
  
  for(int i=0;i<NUMPIXELS;i++){
    double level = levels[i];

    if (level < goals[i]) {
      level = min(level + rise, MAX);
      if (level > (MAX - MAX/100)) {
        
        pullAdjacent(i+1, 1 + dropoff); 
      }
    }
    else {

      goals[i] = 0;
      level = max(level - fall, minLevel);
    }

    int r = random(choose);
    if (r == 0) {
      goals[i] = MAX;       
      pullAdjacent(i-1, 1); 
      pullAdjacent(i+1, 1); 
    }

    levels[i] = level;    

    float factor = (float)level / MAX;
    uint32_t color = rgb(235 * factor, 255 * factor * factor, 50 * factor * factor);
    pixels->setPixelColor(i, color);
  }

}

void FireWaveMode::pullAdjacent(int i, int pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  int level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
