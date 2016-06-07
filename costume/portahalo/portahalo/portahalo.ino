#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

/* PIN ASSIGNMENT */

//Input
#define BUTTON_MODE       2 

//Output
#define HALO_OUT          0

/* OTHER STUFF */

#define BUTTON_THRESHOLD 50

#define NUMPIXELS      60

#define LAST           NUMPIXELS-1

#define PIXEL_DELAY 10

#define MODES 2

#define MAX            32767

#define rise 0.05 * MAX
#define fall 0.02 * MAX
#define dropoff 0.25 * MAX
#define minLevel 0.15 * MAX
#define choose 120

Adafruit_NeoPixel halo = Adafruit_NeoPixel(NUMPIXELS, HALO_OUT, NEO_GRB + NEO_KHZ800);

int mode = 2;

int discoState = 0;

boolean buttonHistory[3];

int levels [NUMPIXELS];
int goals [NUMPIXELS];

void setup() {  
 if(F_CPU == 16000000) clock_prescale_set(clock_div_1); 

  halo.begin();
  halo.setBrightness(255);
  
  for (int state = 0; state < 3; state++) {
    buttonHistory[state] = false;
  }
  
  for (int i=0; i<NUMPIXELS; i++) {
    levels[i] = 0; 
    goals[i] = MAX;
  }
}

void updateButtonState() {
  boolean current = analogRead(BUTTON_MODE) > BUTTON_THRESHOLD;

  buttonHistory[3] = buttonHistory[2];  
  buttonHistory[2] = buttonHistory[1];
  buttonHistory[1] = buttonHistory[0];
  buttonHistory[0] = current;
}

void discoStep() {
  
  if (discoState > 1024) {
    discoState = 0;
  }
  
  int offset = discoState / 1;
  
  int state = discoState / 4;
  
  int mode = discoState / 32;

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {
    int a = NUMPIXELS - i;
    
    int iOffset = ((offset / 32) %2 == 0)? a - offset : a + offset;
    
    int quad = (int)(((float)iOffset / NUMPIXELS) * 4) % 4;
    
    color = 1;//hue((discoState / 128.0) * 255 + quad * (255.0 / 4.0));
    
    if (quad % 2 == state % 2) {
      color = 0;
    }
    
    halo.setPixelColor(i, color);
  }

  discoState++;
}

void fireStep() {

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

    float factor = 1;//(float)level / MAX;
    halo.setPixelColor(i, halo.Color(235 * factor, 255 * factor * factor, 50 * factor * factor));

  }
  
}

void pullAdjacent(int i, int pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  int level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}

void loop() { 
  
  updateButtonState();
  
  if (buttonHistory[0] && buttonHistory[1] && !buttonHistory[2]) {
    mode = (mode == 1) ? 2 : 1;
  }
  
    for(int i=0;i<NUMPIXELS;i++){

    halo.setPixelColor(i, halo.Color(i *4, 255-(i*4), 128));

  }
  
//  fireStep();
  if (mode == 1) {
    
  } else {
    //discoStep();
  }
  
  halo.show(); 
  
  delay(PIXEL_DELAY);
}

