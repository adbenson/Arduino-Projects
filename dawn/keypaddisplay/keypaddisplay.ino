#include <Time.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

#define MODE_RUN 0
#define MODE_SET_TIME 1
#define MODE_SET_ALARM 2
#define MODE_SET_DURATION 3

#define LED_DISPLAY_PIN 12
#define LED_DISPLAY_IN 13

#define LED_COLON B00010000
#define LED_PM B00001000

byte currentMode = 0;
byte dotState = B00000000;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},  {'4','5','6'},  {'7','8','9'},  {'*','0','#'}
};
byte rowPins[ROWS] = {3, 8, 7, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 2, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

SoftwareSerial LEDSerial(LED_DISPLAY_IN, LED_DISPLAY_PIN);

long lastTick;

int alarmHr;
int alarmMin;
int duration;

void setup(){
  Serial.begin(9600);
  
  setTime(12, 0, 0, 1, 1, 2012);
  alarmHr = 12;
  alarmMin = 12;
  
  pinMode(LED_DISPLAY_PIN, OUTPUT);
  pinMode(LED_DISPLAY_IN, INPUT);
  
  LEDSerial.begin(9600);
  LEDSerial.print("v"); //Reset
  LEDSerial.print("w"); //Dot mode
  LEDSerial.print(dotState); //Clear all dots
  
  LEDSerial.print("HELO");
  
  lastTick = millis() - 1000;
  
  int h = hour();
  int m = minute();
  inputTime(h, m);
  setTime(h, m, 0, 1, 1, 2012);
}

void loop(){
  char key = keypad.getKey();
  int* time;

  if (key != NO_KEY){
    Serial.println(key);
         
    if (key >= '0' && key <= '9') {
      int h = hour();
      int m = minute();
      inputTime(h, m);
      setTime(h, m, 0, 1, 1, 2012);
    }
    
    if (key == '*') {
      changeMode();
    }
  }
  
  if (millis() - lastTick >= 1000) {
    lastTick = millis();
    toggleColon();
  }
}

void changeMode() {
  currentMode++;
  currentMode %= 4;
  
  LEDSerial.write("w"); //Set decimal mode
  byte led = 2 << currentMode;
  LEDSerial.write(led);
}

void toggleColon() {
  dotState ^= LED_COLON;
  
  Serial.println(dotState);
  showDots();
}

void inputTime(int &h, int &m) {
  int digit = 0;
  int digits[4];
  showTime(h, m);
  
  while(digit < 4) {
    char key = keypad.getKey();
    boolean valid = false;

    if (key >= '0') {
      int value = key - '0';

      switch(digit) {
        case 0:
          if (value <= 2) valid = true;
          break;
        case 1:
          if (value <= 4 && (digits[0] == 2 || value <= 2)) {
            valid = true;
          }
          break;
        case 2:
          if (value <= 5) valid = true;
          break;
        case 3:
          if (value <= 9) value = true;
          break;        
      }
      
      Serial.print(value);
      if (valid) {
        Serial.println(" okay");
        digits[digit] = value;
        digit++;
        
        h = (digits[0] * 10) + digits[1];
        m = (digits[2] * 10) + digits[3];
        showTime(h, m);
      }
    }
  }
}

void showDots() {
  LEDSerial.write("w");
  LEDSerial.write(dotState);
}

void showTime(int h, int m) {
  byte h1 = (byte) h / 10;
  byte h2 = (byte) h % 10;
  byte m1 = (byte) m / 10;
  byte m2 = (byte) m % 10;
  
  LEDSerial.write("v");
  LEDSerial.write(h);
//  LEDSerial.write(h2);
  LEDSerial.write(m);
//  LEDSerial.write(m2);
}

