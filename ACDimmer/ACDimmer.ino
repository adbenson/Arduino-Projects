#include <TimerOne.h> 

#define LED_OUT 13
#define SSR_OUT 11
#define ZEROCROSS_IN 2
#define AC_FREQ_HZ 60

volatile long turnOnTime;
volatile boolean ssrOn;

int checkPeriod_us = 30;

int halfCycleTime_us = 1000000 / (2 * AC_FREQ_HZ);
int stayOffTime_us;

float dutyCycle;

void setup() {
  pinMode(LED_OUT, OUTPUT);
  digitalWrite(LED_OUT, HIGH);
  pinMode(SSR_OUT, OUTPUT);
  digitalWrite(SSR_OUT, HIGH);  
  
  //Enable zero-cross input and pullup resistance
  pinMode(ZEROCROSS_IN, INPUT);
  digitalWrite(ZEROCROSS_IN, HIGH);
  
  turnOnTime = 0;
  ssrOn = true;
  dutyCycle = 0;
  stayOffTime_us = halfCycleTime_us;
  
  attachInterrupt(ZEROCROSS_IN - 2, zeroCrossHandler, RISING);
  
  Timer1.initialize(halfCycleTime_us/2);
  Timer1.attachInterrupt(checkTime, halfCycleTime_us/2);
  
  Serial.begin(115200);
}

void zeroCrossHandler() {
  ssrOn = false;
  digitalWrite(SSR_OUT, LOW);
  digitalWrite(LED_OUT, LOW);
  
  turnOnTime = micros() + stayOffTime_us;  
  
//  Serial.println(turnOnTime);
}

void checkTime() {
// if (!ssrOn && micros() >= turnOnTime) {
    ssrOn = true;
    digitalWrite(SSR_OUT, HIGH);
    digitalWrite(LED_OUT, HIGH);
// } 
}

void loop() {
  dutyCycle += 0.05;
  if (dutyCycle > 1.0) {
     dutyCycle = 0; 
  }
  
  stayOffTime_us = (halfCycleTime_us * dutyCycle);
  
  Serial.println(turnOnTime);
  delay(1000);
}
