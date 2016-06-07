#include <Charliplexing.h>

#define minX 0
#define maxX 13
#define minY 0
#define maxY 8

int current = 0;


void setup() {
  LedSign::Init();  //Initializes the screen
}

void loop() {
  int currX, currY, startY;
  
  LedSign::Clear();
  
  for (int x = minX; x <= maxX; x++) {

    if (x % 2 == 0)
      startY = minY;
    else
      startY = maxY;
      
    vert(x, startY);      

    delay(33);
  }
}

void vert(int x, int startY) {
  int dir, endY;
  
  if (startY > (maxY / 2))
    dir = 1; //Down
  else
    dir = -1; //Up
  
  for (int y = startY; y += dir) {
    
    LedSign::Set(x, y, 1);
  }
}

void down() {
  
}


