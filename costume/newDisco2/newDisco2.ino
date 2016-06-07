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

  uint32_t colors[16] = {
    hue(0),
    hue(16),
    hue(32),
    hue(48),
    hue(64),
    hue(80),
    hue(96),
    hue(112),
    hue(128),
    hue(144),
    hue(160),
    hue(176),
    hue(192),
    hue(208),
    hue(224),
    hue(240),
  };

  uint16_t i, j;


  for(int phase = 2; phase<3; phase++) {
    for(int s=0; s<16; s++) {
      for (int i=0; i<PIXEL_COUNT / 2; i++) {
        int alt = s % 2;
        int n = i*2;
        int m = PIXEL_COUNT - (n + 1);
        uint32_t color = colors[(i + s) % 16];

        n+= alt;
        m+= alt;
        switch(phase){
          case 0: set(n, color);
                  set(m, 0);
                  break;
          case 1: set(n, 0);
                  set(m, color);
                  break;
          case 2: set(n, color);
                  set(m, color);
                  break;
          case 3: set(n, 0);
                  set(m, color);
                  break;
        }
        
      }
      strip.show();
      delay(100);
    }
  }
}

void set(int n, uint32_t color) {
  strip.setPixelColor(n, color);
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

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
