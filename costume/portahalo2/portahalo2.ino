// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define OUT_PIN      0

#define SWITCH_PIN   3

#define SLEEP_DELAY  200

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

#define MAX            32767

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, OUT_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
double rise = 0.07;
double fall = 0.02;
double dropoff = 0.25;
double minLevel = 0.15;
int choose = 120;
double potMax = 850;

double levels [NUMPIXELS];
double goals [NUMPIXELS];

int discoState = 1;

boolean hasBeenPressed = false;
int previousButton;

int mode = 1;

void setup() { 
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(255);
  
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  for(int i=0; i<NUMPIXELS; i++) {
    levels[i] = 0; 
    goals[i] = 1;
  }
}

void pullAdjacent(int i, double pull) {
  i = ((i<0)? LAST : i);
  i = (i>LAST)? 0 : i;

  double level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}

void fire() {
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
    if (r == 0 || (i >= 30 && i <= 31 && r < (choose/10))) {
      double goal = random(level * 1000, 1000) / 1000.0;
      goals[i] = 1;        
      pullAdjacent(i-1, 1); 
      pullAdjacent(i+1, 1); 
    }

    levels[i] = level;    
    pixels.setPixelColor(i, pixels.Color(255, 255 * level * level, 50 * level * level));

  }
}

int quadrant(int i) {
   return (int)(((float)i / NUMPIXELS) * 4) % 4;
}

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t hue(byte hue) {
  hue = 255 - (hue % 255);
  
  if (hue < 85) {
    return rgb(255 - hue * 3, 0, hue * 3);
  } else if (hue < 170) {
    hue -= 85;
    return rgb(0, hue * 3, 255 - hue * 3);
  } else {
    hue -= 170;
    return rgb(hue * 3, 255 - hue * 3, 0);
  }
}

void disco() {
  
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
    
    int quad = quadrant(iOffset);
    
    color = hue((discoState / 128.0) * 255 + quad * (255.0 / 4.0));
    
    if (quad % 2 == state % 2) {
      color = 0;
    }
    
    pixels.setPixelColor(i, color);
  }

  discoState++;
}

boolean buttonPressed() {
  boolean pressed = false;

  int button = digitalRead(SWITCH_PIN);

  //If we detected a button press last cycle  and it's still pressed, go for it!
  if (hasBeenPressed && button == HIGH) {
    pressed = true;
    //Reset the watcher
    hasBeenPressed = false;
  }

  //The button just went down. Don't do anything until we've confirmed it's still down next cycle.
  if (button == LOW && previousButton == HIGH) {
    hasBeenPressed = true;
  }

  previousButton = button;

  return pressed;
}

void loop() { 

  if (buttonPressed()) {
    mode = mode==1? 2 : 1;
  }

  if (mode == 1) {
    fire();
  }
  else {
    disco();
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  delay(delayval); // Delay for a period of time (in milliseconds).
}



