

#include <TimerOne.h>           // Avaiable from http://www.arduino.cc/playground/Code/Timer1

volatile int i = 0;               // Variable to use as a counter
volatile boolean zero_cross = false;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 11;                // Output to Opto Triac
int ZC_PIN = 2;
int dim = 64;                    // Dimming level (0-128)  0 = on, 128 = 0ff

int freqStep = 65;    // This is the delay-per-brightness step in microseconds.
// It is calculated based on the frequency of your voltage supply (50Hz or 60Hz)
// and the number of brightness steps you want. 
// 
// The only tricky part is that the chopper circuit chops the AC wave twice per
// cycle, once on the positive half and once at the negative half. This meeans
// the chopping happens at 120Hz for a 60Hz supply or 100Hz for a 50Hz supply. 

// To calculate freqStep you divide the length of one full half-wave of the power
// cycle (in microseconds) by the number of brightness steps. 
//
// (1000000 uS / 120 Hz) / 128 brightness steps = 65 uS / brightness step
//
// 1000000 us / 120 Hz = 8333 uS, length of one half-wave.

void setup() {                                      // Begin setup
  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  
  pinMode(ZC_PIN, INPUT);
  digitalWrite(ZC_PIN, HIGH);
  attachInterrupt(ZC_PIN - 2, zero_cross_detect, CHANGE);   // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);                                              
}

void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
}                                 

// Function will fire the triac at the proper time
void dim_check() {                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH);       
      i=0;                         
      zero_cross = false;                
    } 
    else {
      i++;                           
    }                                
  }                                  
}                                   

void loop() {                        

  
}

