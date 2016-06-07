#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Time.h>

#define LAMP_OUTPUT_PIN 9
#define DISPLAY_OUTPUT_PIN 10
#define DISPLAY_INPUT_PIN 11

#define TICK_MS 1000
#define DUTY_CYCLE_MAX 1023

#define CLOCK_BLINK_INTERRUPT_COUNT 15625

const float DURATION_MIN = 15;
const int PERCEPTION_CURVE = 6;

const int ALARM_HR = 6;
const int ALARM_MIN = 30;

#define LED_COLON B00010000
volatile byte dotState = B00000000;
volatile boolean blink_enable;

byte currentMode = 0;

int fadeStartHr;
int fadeStartMin;

long durationMS;
long fadeStart;

boolean run;

SoftwareSerial LEDSerial(DISPLAY_INPUT_PIN, DISPLAY_OUTPUT_PIN);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'}, {'4','5','6'}, {'7','8','9'}, {'*','0','#'}
};
byte rowPins[ROWS] = {3, 8, 7, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 2, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

long lastTick;

void setup() {
  lastTick = millis();

  pinMode(DISPLAY_OUTPUT_PIN, OUTPUT);
  pinMode(DISPLAY_INPUT_PIN, INPUT);  

  fadeStartMin = ALARM_MIN - DURATION_MIN;
  fadeStartHr = ALARM_HR;
  if (fadeStartMin < 0) {
    fadeStartMin += 60;
    fadeStartHr--;
    if (fadeStartHr < 1) {
      fadeStartHr = 24;
    }
  }

  Serial.begin(9600);

  Serial.print("Start ");
  Serial.print(fadeStartHr);
  Serial.print(":");
  Serial.println(fadeStartMin);

  setupPWM();

  pinMode(LAMP_OUTPUT_PIN, OUTPUT);

  durationMS = DURATION_MIN * 60 * 1000;

  run = false;

  LEDSerial.begin(9600);
  LEDSerial.write("v"); //Reset
  LEDSerial.write("w"); //Dot mode
  LEDSerial.write((byte)B00010000); //clear dots
  LEDSerial.write("HELO");

  int digits[4] = {
    1, 2, 0, 0  };
  int digit = 0;

  boolean blinkOn = true;
  while(digit < 4) {
    if (millis() - lastTick > 500) {
      blinkOn = !blinkOn;
      lastTick = millis();
    }
    char key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      digits[digit] = (int) (key - '0');
      digit++;
    }

    for(int i=0; i<4; i++) {
      Serial.println(blinkOn);
      if (i == digit && blinkOn) {
        LEDSerial.write("x");
      }
      else {
        LEDSerial.write(digits[i]);
      }
    }

    delay(100);
  }

  setTime(
  (digits[0]*10 + digits[1]),
  (digits[2]*10 + digits[3]),
  0, 1, 1, 2012);

}


void loop() {

  time_t t = now();
  if (!run && hour(t) == fadeStartHr && minute(t) == fadeStartMin) {
    fadeStart = millis();
    run = true;

    Serial.println("RUNNNING");
  }

  int h = hour();
  int m = minute();
  if (h >= 10) {
    LEDSerial.write((byte)h/10);
  }
  else {
    LEDSerial.write("x"); 
  }
  LEDSerial.write((byte)h%10);
  LEDSerial.write((byte)m/10);
  LEDSerial.write((byte)m%10);

  if (run) {
    double fadeElapsed = millis() - fadeStart;

    double fadeProgress = fadeElapsed / durationMS;
    fadeProgress = pow(fadeProgress, PERCEPTION_CURVE);

    int value = (fadeProgress * DUTY_CYCLE_MAX) + 1;
    value = min(DUTY_CYCLE_MAX, value);

    //writeAnalog bug - 255 is hard coded as max value, even though I've changed it
    if (value == 255) {
      value = 254;
    }

    Serial.println(value);

    analogWrite(LAMP_OUTPUT_PIN, value);

    if (value >= DUTY_CYCLE_MAX) {
      run = false;
      digitalWrite(LAMP_OUTPUT_PIN, HIGH);

      pinMode(13, OUTPUT);
      digitalWrite(13, HIGH);

      Serial.println("FINISHED");
    }
  }

  delay(TICK_MS);

}

void setupPWM() {

  /**********************************************************************************/
  // Set pwm clock divider
  /**********************************************************************************/
  TCCR1B &= ~(1 << CS12);
  TCCR1B  |=   (1 << CS11);
  TCCR1B &= ~(1 << CS10);  


  /**********************************************************************************/
  // Set pwm resolution  to mode 7 (10 bit)
  /**********************************************************************************/

  TCCR1B &= ~(1 << WGM13);    // Timer B clear bit 4
  TCCR1B |=  (1 << WGM12);    // set bit 3

  TCCR1A |= (1 << WGM11);    //  Timer A set bit 1 
  TCCR1A |= (1 << WGM10);    //  set bit 0

}

void setupInterrupt() {
    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = CLOCK_BLINK_INTERRUPT_COUNT;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}

ISR(TIMER1_COMPA_vect) {
    dotState ^= LED_COLON;
  
    LEDSerial.write("w");
    LEDSerial.write(dotState);
}

