
#include <Adafruit_NeoPixel.h>

#include "FireMode.h"
#include "RainbowMode.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define OUT_PIN      8

#define BUTTON_PIN   4 

#define POT_PIN      A0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

#define LAST           NUMPIXELS-1


FireMode fire;
RainbowMode rainbow;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, OUT_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;

double potMax = 850;

int rainbowState = 0;
int chaseState = 0;
int discoState = 0;

int mode = 1;
int modes = 3;

boolean hasBeenPressed = false;
int previousButton;


void setup() {   
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pixels.begin(); // This initializes the NeoPixel library.
  
  fire = FireMode();
  rainbow = RainbowMode();
}

boolean buttonPressed() {
  boolean pressed = false;

  int button = digitalRead(BUTTON_PIN);

  //If we detected a button press last cycle and it's still pressed, go for it!
  if (hasBeenPressed && button == LOW) {
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

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow() {
  if (chaseState >= 6 * 3) {
    chaseState = 0;
  }

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {
    int offset = (i + (chaseState/3)) % 6;
    switch (offset) {
    case 0: 
      color = pixels.Color(127, 0, 0); 
      break;
    case 1: 
      color = pixels.Color(127, 63, 0); 
      break;
    case 2: 
      color = pixels.Color(127, 127, 0); 
      break;
    case 3: 
      color = pixels.Color(0, 127, 0); 
      break;
    case 4: 
      color = pixels.Color(0, 0, 255); 
      break;
    case 5: 
      color = pixels.Color(63, 0, 255); 
      break;
    }
    pixels.setPixelColor(i, color);
  }

  chaseState++;
}

int quadrant(int i) {
   return (i / NUMPIXELS) / 4;
}

//Theatre-style crawling lights with rainbow effect
void disco() {
  if (discoState > 10) {
    discoState = 0;
  }

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {   
    if ((quadrant(i) % 2) != (discoState / 5)) {
      int n = (i + discoState) % 255;
      color = pixels.Color(255 - n, n, 255);
    }
    else {
      color = 0;  
    }
    pixels.setPixelColor(i, color);
  }

  discoState++;
}

void loop() { 
  
  uint32_t * pix;

  double dial = (analogRead(POT_PIN) / potMax);
  int brightness = min(dial * 255, 255);
  pixels.setBrightness(brightness);

  if (buttonPressed()) {
    mode = (mode == modes)? 1 : mode + 1;
  }
  
  switch (mode) {
    case 1: 
      pix = fire.step();
      for (int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pix[i]);
      }
      break;
    case 2: 
      theaterChaseRainbow(); 
      break;
    case 3: 
      pix = rainbow.step();
      for (int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pix[i]);
      }
      break;
    case 4: 
      disco();
      break;
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  delay(delayval); // Delay for a period of time (in milliseconds).
}


