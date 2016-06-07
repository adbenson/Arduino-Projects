/*
AC Light Control
 
 Updated by Robert Twomey <rtwomey@u.washington.edu>
 
 Changed zero-crossing detection to look for RISING edge rather
 than falling.  (originally it was only chopping the negative half
 of the AC wave form). 
 
 Also changed the dim_check() to turn on the Triac, leaving it on 
 until the zero_cross_detect() turn's it off.
 
 Ryan McLaughlin <ryanjmclaughlin@gmail.com>
 
 The hardware consists of an Triac to act as an A/C switch and 
 an opto-isolator to give us a zero-crossing reference.
 The software uses two interrupts to control dimming of the light.
 The first is a hardware interrupt to detect the zero-cross of
 the AC sine wave, the second is software based and always running 
 at 1/128 of the AC wave speed. After the zero-cross is detected 
 the function check to make sure the proper dimming level has been 
 reached and the light is turned on mid-wave, only providing 
 partial current and therefore dimming our AC load.
 
 Thanks to http://www.andrewkilpatrick.org/blog/?page_id=445 
 and http://www.hoelscher-hi.de/hendrik/english/dimmer.htm
 
 */

#include <TimerOne.h>           // Avaiable from http://www.arduino.cc/playground/Code/Timer1

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 11;                // Output to Opto Triac
int ZC_PIN = 2;
int POT_pin = 0;             // Pot for testing the dimming
int LED = 13;                    // LED for testing
int dim = 0;                    // Dimming level (0-128)  0 = on, 128 = 0ff

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
  pinMode(LED, OUTPUT);                             // Set the LED pin as output
  pinMode(ZC_PIN, INPUT);
  digitalWrite(ZC_PIN, HIGH);
  attachInterrupt(ZC_PIN - 2, zero_cross_detect, RISING);   // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);      
  // Use the TimerOne Library to attach an interrupt
  // to the function we use to check to see if it is 
  // the right time to fire the triac.  This function 
  // will now run every freqStep in microseconds.     
  Serial.begin(115200);  
}

void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
  digitalWrite(LED, LOW);
}                                 

// Function will fire the triac at the proper time
void dim_check() {                   
  if(zero_cross == true) {   
    if(i>=dim) {                     
//      digitalWrite(AC_pin, HIGH); 
        digitalWrite(LED, HIGH);
      i=0;                         
      zero_cross = false;                
    } 
    else {
      i++;                           
    }                                
  }                                  
}                                   

void loop() {                        
//  dim = analogRead(POT_pin) / 8;  
//  dim = 64;
//  analogWrite(LED, dim);
    dim++;
    if (dim > 128) {
      dim = 0;
    }
  
  delay(500);
}


