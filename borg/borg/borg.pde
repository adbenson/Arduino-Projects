#include <Charliplexing.h>

#define minX 0
#define maxX 14
#define minY 0
#define maxY 9

int startX, endX;
boolean toggle;

int offsets[9] = {-3, -1, 0, 0, 0, 0, 0, -1, -3};

void setup() {
  LedSign::Init();  //Initializes the screen

  startX = minX;
  endX = 1;
  
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
}

void loop() {
  toggle = !toggle;
 
   for (int y=minY; y<maxY; y++) {
  
    int tempX = (startX+offsets[y]) % maxX;
    if (tempX < 0) {
       tempX = maxX + tempX; 
    }
    LedSign::Set(tempX, y, 0);
    tempX = (endX+offsets[y]) % maxX;
    LedSign::Set(tempX, y, 1);
     
   }
   
   startX++;
   endX++;
   if (startX >= maxX) {
      startX = minX;
      endX = maxX / 2;
   }
   
   int migrate = random(maxY);
   int dir = random(3) - 1;
   int newVal = dir + offsets[migrate];
   boolean move = true;
   if (migrate > 1) {
     if (abs(newVal - offsets[migrate-1]) > 1)
      move = false;
   }
   if (migrate < maxY-1) {
      if (abs(newVal - offsets[migrate+1]) > 1) 
        move = false;
   }
   if (move) {
      offsets[migrate] = newVal; 
   }

   
   delay(100);
   
}

void blob(int x, int y, int v, int s) {
 
   for(int i=0; i<s; i++) { 
     LedSign::Set(x, y, v);
     
     LedSign::Set(x-i, y, v);
     LedSign::Set(x+1, y, v);
     LedSign::Set(x, y-1, v);
     LedSign::Set(x, y+1, v);


      delay(10);     
   }
}

