/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
 
 #include <limits.h>

// These constants won't change.  They're used to give names
// to the pins used:
const int flexPin = 3;  // Analog input pin that the potentiometer is attached to
const int switchPin = 1;
const int lightPin = 0; // Analog output pin that the LED is attached to

float sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

float sensorMin = INT_MAX;
float sensorMax = INT_MIN;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  
  
  // read the analog in value:
  sensorValue = analogRead(flexPin);
  
  sensorMin = min(sensorValue, sensorMin);
  sensorMax = max(sensorValue, sensorMax);
  
  // map it to the range of the analog out:
  outputValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  // change the analog out value:
  analogWrite(lightPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = " );
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
