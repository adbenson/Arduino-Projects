// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define OUT_PIN      0

#define POT_PIN      1

#define SWITCH_PIN   3

#define SLEEP_DELAY  200

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
#define LAST           NUMPIXELS-1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, OUT_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
double rise = 0.07;
double fall = 0.02;
double dropoff = 0.25;
double minLevel = 0.15;
int choose = 120;
double potMax = 850;

int chaseState = 0;

double levels [NUMPIXELS];
double goals [NUMPIXELS];

boolean hasBeenPressed = false;
int previousButton;

boolean on = true;

void setup() { 
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);

  pixels.begin(); // This initializes the NeoPixel library.
  
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  for(int i=0; i<NUMPIXELS; i++) {
    levels[i] = 0; 
    goals[i] = 1;
  }
}

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void chase() {

  if (chaseState >= 6 * 3) {
    chaseState = 0;
  }

  uint32_t color;
  for (int i=0; i < NUMPIXELS; i++) {
    int offset = (i + (chaseState/3)) % 6;
    switch (offset) {
    case 0: 
      color = rgb(127, 0, 0); 
      break;
    case 1: 
      color = rgb(127, 63, 0); 
      break;
    case 2: 
      color = rgb(127, 127, 0); 
      break;
    case 3: 
      color = rgb(0, 127, 0); 
      break;
    case 4: 
      color = rgb(0, 0, 255); 
      break;
    case 5: 
      color = rgb(63, 0, 255); 
      break;
    }
    
    pixels.setPixelColor(i, color);
  }

  chaseState++;
  
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
    on = !on; 
    
    if (!on) {
      pixels.setBrightness(0);
      pixels.show();
    }
  }

  if (!on) {
    delay(SLEEP_DELAY);
    return; 
  }

  pixels.setBrightness(255);

  chase();

  pixels.show(); // This sends the updated pixel color to the hardware.

  delay(delayval); // Delay for a period of time (in milliseconds).
}



