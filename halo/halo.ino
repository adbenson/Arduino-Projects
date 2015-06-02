
#include <Adafruit_NeoPixel.h>

#include "FireMode.h"
#include "RainbowMode.h"
#include "ChaseMode.h"
#include "DiscoMode.h"

#define HALO_OUT      3

#define BUTTON_A  10
#define BUTTON_B  11 
#define BUTTON_C  12 
#define BUTTON_D  13 

#define DIAG  13 

#define POT_PIN  A5

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

#define LAST           NUMPIXELS-1

const byte BUTTON_THRESHOLD = 50;

FireMode fire;
ChaseMode chase;
RainbowMode rainbow;
DiscoMode disco;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, HALO_OUT, NEO_GRB + NEO_KHZ800);

int delayval = 10;

double potMax = 850;

int discoState = 0;

int mode = 1;
int modes = 4;

boolean hasBeenPressed = false;
int previousButton;


void setup() {   
  pinMode(BUTTON_C, INPUT); 
  
  pinMode(DIAG, OUTPUT);

  pixels.begin(); // This initializes the NeoPixel library.

  fire = FireMode();
  chase = ChaseMode();
  rainbow = RainbowMode();
  disco = DiscoMode();
}

boolean buttonPressed() {
  boolean pressed = false;

  int button = digitalRead(BUTTON_C);

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
  
  uint32_t * pix;

//  double dial = (analogRead(POT_PIN) / potMax);
  int brightness = 255;//min(dial * 255, 255);
  pixels.setBrightness(brightness);

  if (buttonPressed()) {
    mode++;
    if (mode > modes) {
       mode = 1;
    }
  }
  
  switch (mode) {
    case 1: 
      pix = fire.step();
      break;
    case 2: 
      pix = chase.step();
      break;
    case 3: 
      pix = rainbow.step();
      break;
    case 4: 
      pix = disco.step();
  }
  
  for (int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pix[i]);
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  delay(delayval); // Delay for a period of time (in milliseconds).
}


