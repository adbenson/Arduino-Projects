// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16
#define LAST           NUMPIXELS-1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100;
double level [NUMPIXELS];

int tempColor[3];

void setup() { 
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  
  for(int i=0; i<NUMPIXELS; i++) {
      level[i] = 1.0/i; 
  }
  
//  Serial.println("Begin");
}

void getRGB(int hue, int sat, int val) { 
 
  int r;
  int g;
  int b;
  int base;
 
  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    tempColor[0]=val;
    tempColor[1]=val;
    tempColor[2]=val;  
  } else  { 
 
    base = ((255 - sat) * val)>>8;
 
    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;
 
    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;
 
    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;
 
    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;
 
    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;
 
    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }
 
    tempColor[0]=r;
    tempColor[1]=g;
    tempColor[2]=b; 
  }   
}

void loop() {
  
  
  for(int i=0;i<NUMPIXELS;i++){
    double hue = level[i];
    hue += 0.01;
    if (hue > 1) {
      hue = 0;
    }
    level[i] = hue;    
    
    getRGB(hue * 255, 255, 150);

    pixels.setPixelColor(i, tempColor[0], tempColor[1], tempColor[2]);

  }
  
  pixels.show(); // This sends the updated pixel color to the hardware.
  
  delay(delayval); // Delay for a period of time (in milliseconds).
}


