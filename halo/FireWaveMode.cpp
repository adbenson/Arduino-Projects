#include "Arduino.h"
#include "FireWaveMode.h"

uint32_t * FireWaveMode::step() {

  for(int i=0;i<NUMPIXELS;i++){
    double level = levels[i];

    if (level < goals[i]) {
      level = min(level + rise, 1);
      if (level > 0.99) {
        
        pullAdjacent(i+1, 1 + dropoff); 
      }
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

    pixels[i] = rgb(235 * level, 255 * level * level, 50 * level * level);

  }
  
  return pixels;

}

void FireWaveMode::pullAdjacent(int i, double pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  double level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
