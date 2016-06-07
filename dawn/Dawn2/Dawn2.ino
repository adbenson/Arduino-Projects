#include <Time.h>

#define OUTPUT_PIN 10
#define TICK_MS 1000
#define DUTY_CYCLE_MAX 1023

const float DURATION_MIN = 15;
const int PERCEPTION_CURVE = 6;

const int ALARM_HR = 6;
const int ALARM_MIN = 30;

const int START_HR = 22;
const int START_MIN = 20;

int fadeStartHr;
int fadeStartMin;

long durationMS;
long fadeStart;

boolean run;

void setup() {
  
  setTime(START_HR, START_MIN, 0, 1, 1, 2012);
  
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
  
  pinMode(OUTPUT_PIN, OUTPUT);
    
  durationMS = DURATION_MIN * 60 * 1000;
  
  run = false;
}


void loop() {
  
  time_t t = now();
  if (!run && hour(t) == fadeStartHr && minute(t) == fadeStartMin) {
      fadeStart = millis();
      run = true;
      
      Serial.println("RUNNNING");
  }
    
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
      
    analogWrite(OUTPUT_PIN, value);
    
    if (value >= DUTY_CYCLE_MAX) {
       run = false;
       digitalWrite(OUTPUT_PIN, HIGH);
       
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
