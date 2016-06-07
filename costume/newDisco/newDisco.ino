// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define BUTTON_PIN   1    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    0    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 60

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;

void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  crossChase();
//  // Get current button state.
//  bool newState = digitalRead(BUTTON_PIN);
//
//  // Check if state changed from high to low (button press).
//  if (newState == LOW && oldState == HIGH) {
//    // Short delay to debounce button.
//    delay(20);
//    // Check if button is still low after debounce.
//    newState = digitalRead(BUTTON_PIN);
//    if (newState == LOW) {
//      showType++;
//      if (showType > 9)
//        showType=0;
//      startShow(showType);
//    }
//  }
//
//  // Set the last button state to the old state.
//  oldState = newState;
}

void startShow(int i) {
  switch(i){
    case 0: crossChase();
            break;
    case 1: crossChase();
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}

void crossChase() {
  int half = strip.numPixels() / 2;

  uint32_t colors[6] = {
    hue(0),
    hue(42),
    hue(85),
    hue(127),
    hue(170),
    hue(200)
  };

  uint16_t i, j;

  for(int s=0; s<6; s++) {
    for (int i=0; i<PIXEL_COUNT / 2; i++) {
      int alt = i % 2;
      int n = i*2;
      int m = PIXEL_COUNT - (n + 1);
      uint32_t color = colors[(i + s) % 6];

      strip.setPixelColor(n, color);
      strip.setPixelColor(m, color);
    }
    strip.show();
    delay(30);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, hue((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, hue(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, hue( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t hue(byte huePos) {
  huePos = 255 - huePos;
  if(huePos < 85) {
    return strip.Color(255 - huePos * 3, 0, huePos * 3);
  }
  if(huePos < 170) {
    huePos -= 85;
    return strip.Color(0, huePos * 3, 255 - huePos * 3);
  }
  huePos -= 170;
  return strip.Color(huePos * 3, 255 - huePos * 3, 0);
}
