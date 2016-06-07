
const float perceptionCurve = 5;

const int OUTPUT_PIN = 9;

const int TICK_MS = 10;

const long DURATION_MIN = 1;

double durationMs;

//Overall cycle time in microseconds
//Higher = better granularity (smaller steps)
//Lower = reduces flicker
//Never go above 30,000 or flicker will be visible
const int CYCLE_MICROS = 10000;

long lastTick;
long fadeStart;
double dutyCycle;

int high;
int low;

void setup()  {
  Serial.begin(9600);
  
  durationMs = DURATION_MIN * 60 * 1000;
  
  dutyCycle = 0;
  pinMode(OUTPUT_PIN, OUTPUT);
  
  pinMode(13, OUTPUT);
  
  high = 0;
  low = CYCLE_MICROS;
  
  fadeStart = millis();
} 

void loop()  {
  long time = millis();
  
  if (time - lastTick > TICK_MS) {
    lastTick = time; 
    
    long fadeTime = time - fadeStart;
    
    dutyCycle = fadeTime / durationMs;
  
    dutyCycle = pow(dutyCycle, perceptionCurve);

    if (dutyCycle > 1) {
      dutyCycle = 0;
      fadeStart = millis();
        digitalWrite(OUTPUT_PIN, HIGH);
        delay(1000);
         digitalWrite(OUTPUT_PIN, LOW);
        delay(1000);
    }

    dutyCycle = min(1, dutyCycle);
    
    high = CYCLE_MICROS * dutyCycle;
    low = CYCLE_MICROS - high;
  }
  Serial.println(high);
  
  if (high > 3) {
    digitalWrite(OUTPUT_PIN, HIGH);   // set the LED on
    delayMicroseconds(high);              // wait for a second
  }
  
  if (low > 3) {
    digitalWrite(OUTPUT_PIN, LOW);    // set the LED off
    delayMicroseconds(low);              // wait for a second
  }

}

void lightCycle() {
  

}


