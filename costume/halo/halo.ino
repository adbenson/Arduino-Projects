#include <Adafruit_NeoPixel.h>

#include "FireMode.h"
#include "RainbowMode.h"
#include "ChaseMode.h"
#include "DiscoMode.h"
#include "FireWaveMode.h"

/* PIN ASSIGNMENT */

//Input
#define BUTTON_POWER      0
#define BUTTON_WINGSUP    1 
#define BUTTON_MODE       2 
#define BUTTON_WINGSDOWN  3 

#define WING_POSITION     4
#define BRIGHTNESS_CTRL   5

//Output
#define HALO_OUT          3
#define WINGS_OUT         4

#define WING_SPEED        5
#define WING_DIR          6

#define DIAGNOSTIC_LED  13 

/* OTHER STUFF */

#define BUTTON_THRESHOLD 50

#define NUMPIXELS      60

#define LAST           NUMPIXELS-1

#define BUTTONS 4

#define PIXEL_DELAY 10
#define SLEEP_DELAY  200

#define MODES 2

#define WINGS_STOP -1
#define WINGS_UP    LOW
#define WINGS_DOWN  HIGH

boolean running = true;

FireMode fire;
FireWaveMode fireWave;
ChaseMode chase;
RainbowMode rainbow;
DiscoMode disco;

Adafruit_NeoPixel halo = Adafruit_NeoPixel(NUMPIXELS, HALO_OUT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wing = Adafruit_NeoPixel(NUMPIXELS, WINGS_OUT, NEO_GRB + NEO_KHZ800);

int mode = 1;

boolean buttonHistory[4][4];

int wingState = WINGS_STOP;
int wingSpeed = 0;

void setup() {   
  
  pinMode(DIAGNOSTIC_LED, OUTPUT);
  
  pinMode(WING_SPEED, OUTPUT);
  pinMode(WING_DIR, OUTPUT);
  wingControl(WINGS_STOP);

  halo.begin(); // This initializes the NeoPixel library.
  wing.begin();

  fire = FireMode();
  fireWave = FireWaveMode();
  chase = ChaseMode();
  rainbow = RainbowMode();
  disco = DiscoMode();
  
  for(int button = 0; button < BUTTONS; button++) {
    for (int state = 0; state < 3; state++) {
      buttonHistory[button][state] = false;
    }
  }
}

void diag(boolean on) {
  digitalWrite(DIAGNOSTIC_LED, on? HIGH : LOW);
}

boolean buttonPressed(int button) {
  
  //Only return true once for each press, and only after it has been pressed for at least one cycle.
  boolean pressed = buttonHistory[button][0] && buttonHistory[button][1] && !buttonHistory[button][2]; 

  return pressed;
}

boolean buttonDown(int button) {
  int pressed = 0;
  
  for (int time = 0; time < 4; time++) {
    if (buttonHistory[button][time]) {
     pressed++;
    } 
  }
  
//  boolean pressed = (buttonHistory[button][0] && buttonHistory[button][1]) || (buttonHistory[button][1] && buttonHistory[button][2]);

  return pressed >= 2;
}

void updateButtonState() {
  for(int button = 0; button < BUTTONS; button++) {
    boolean current = analogRead(button) > BUTTON_THRESHOLD;

    buttonHistory[button][3] = buttonHistory[button][2];  
    buttonHistory[button][2] = buttonHistory[button][1];
    buttonHistory[button][1] = buttonHistory[button][0];
    buttonHistory[button][0] = current;
  }
}

void updatePower() {
 
  if (buttonPressed(BUTTON_POWER)) {
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
 
  if (buttonPressed(BUTTON_MODE)) {
    mode++;
    if (mode > MODES) {
       mode = 1;
    }
  }
}

int readBrightness(int pin, int bottom, int top) {
  int potReading = map(analogRead(pin), bottom, top, 255, 0);
  int potBrightness = constrain(potReading, 0, 255);

  return potBrightness;
}

void updateWingControl() {
    
  if (buttonDown(BUTTON_WINGSUP)) {
    wingControl(WINGS_UP);
  }
  else if (buttonDown(BUTTON_WINGSDOWN)) {
    wingControl(WINGS_DOWN);
  }
  else {
    wingSpeed = 0;
    digitalWrite(WING_SPEED, LOW);  
  }
}

void wingControl(int state) {
  wingSpeed += 16;
  wingSpeed = constrain(wingSpeed, 16, 255);

  digitalWrite(WING_DIR, state);
  analogWrite(WING_SPEED, wingSpeed);
}

void loop() { 
  
  updateButtonState();
  
  updatePower();
  
  updateWingControl();

  halo.setBrightness(readBrightness(BRIGHTNESS_CTRL, 1, 1023));
  wing.setBrightness(readBrightness(WING_POSITION, 1, 400));
  
  if (running) {
    updateMode();
    updatePixels();  
  }
  
  delay(PIXEL_DELAY);
}

void updatePixels() { 

  switch (mode) {
    case 1: 
      fire.step(&halo);
      fireWave.step(&wing);
      break;
    case 2: 
      disco.step(&halo);
      disco.step(&wing);
      break;
    case 3: 
      rainbow.step(&halo);
      rainbow.step(&wing);
      break;
    case 4: 
      chase.step(&halo);
      chase.step(&wing);
  }
  

  
  halo.show(); // This sends the updated pixel color to the hardware.
  wing.show(); // This sends the updated pixel color to the hardware.
}


