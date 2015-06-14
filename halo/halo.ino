
#include <Adafruit_NeoPixel.h>

#include "FireMode.h"
#include "RainbowMode.h"
#include "ChaseMode.h"
#include "DiscoMode.h"

#define HALO_OUT      3
#define LWING_OUT     4
#define RWING_OUT     5

#define BUTTON_A  0
#define BUTTON_B  1 
#define BUTTON_C  2 
#define BUTTON_D  3 

#define DIAG  13 

#define POT_PIN  A5

#define BUTTON_THRESHOLD 50

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

#define LAST           NUMPIXELS-1

#define BUTTONS 4

#define PIXEL_DELAY 10
#define SLEEP_DELAY  200

#define MODES 4

boolean running = true;

FireMode fire;
ChaseMode chase;
RainbowMode rainbow;
DiscoMode disco;

Adafruit_NeoPixel halo = Adafruit_NeoPixel(NUMPIXELS, HALO_OUT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wing = Adafruit_NeoPixel(NUMPIXELS, LWING_OUT, NEO_GRB + NEO_KHZ800);

int mode = 1;

boolean buttonHistory[4][3];

void setup() {   
  
  pinMode(DIAG, OUTPUT);

  halo.begin(); // This initializes the NeoPixel library.
  wing.begin();

  fire = FireMode();
  chase = ChaseMode();
  rainbow = RainbowMode();
  disco = DiscoMode();
  
  for(int button = 0; button < BUTTONS; button++) {
    for (int state = 0; state < 2; state++) {
      buttonHistory[button][state] = false;
    }
  }
}

boolean buttonPressed(int button) {
  
  //Only return true once for each press, and only after it has been pressed for at least one cycle.
  boolean pressed = buttonHistory[button][0] && buttonHistory[button][1] && !buttonHistory[button][2]; 

  return pressed;
}

void updateButtonState() {
  for(int button = 0; button < BUTTONS; button++) {
    boolean current = analogRead(button) > BUTTON_THRESHOLD;
  
    buttonHistory[button][2] = buttonHistory[button][1];
    buttonHistory[button][1] = buttonHistory[button][0];
    buttonHistory[button][0] = current;
  }
}

void updatePower() {
 
  if (buttonPressed(BUTTON_A)) {
    running = !running; 
    
      if (!running) {
        halo.setBrightness(0);
        halo.show();
        wing.setBrightness(0);
        wing.show();
      }
  }
   
}


void updateMode() {
 
  if (buttonPressed(BUTTON_C)) {
    mode++;
    if (mode > MODES) {
       mode = 1;
    }
  }
   
}

void loop() { 
  
  updateButtonState();
  
  updatePower();
  
  if (running) {
    updateMode();
    updatePixels();  
  }
  
  delay(PIXEL_DELAY);
}

void updatePixels() { 

  int potReading = map(analogRead(POT_PIN), 0, 1024, 265, 10);
  int brightness = constrain(potReading, 0, 255);
  halo.setBrightness(brightness);
  wing.setBrightness(brightness);

  switch (mode) {
    case 1: 
      fire.step(&halo);
      break;
    case 2: 
      chase.step(&halo);
      break;
    case 3: 
      rainbow.step(&halo);
      break;
    case 4: 
      disco.step(&halo);
  }

  halo.show(); // This sends the updated pixel color to the hardware.
  wing.show(); // This sends the updated pixel color to the hardware.
}


