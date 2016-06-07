#include <Letters.h>
#include <Charliplexing.h>

#define BTN_UP 19
#define BTN_DOWN 18
#define BTN_LEFT 17
#define BTN_RIGHT 16

#define SCR_TOP 0
#define SCR_LEFT 0
#define SCR_RIGHT 13
#define SCR_BOTTOM 8

int buttons[] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT};
int buttonCount = 4;
boolean run = false;

int period = 250;
long nextCycle = -1;


void setup() {
  Serial.begin(9600);
 
  LedSign::Init(); LedSign::Set(1, 1, 1);
  //Letters::init();
  
  randomSeed(analogRead(0));
  
  for (int i=0; i<buttonCount; i++) {
     pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  
  newGame();  
}

void loop() {
  if (run) {
    long currentTime = millis();
    if (nextCycle < 0)
      nextCycle = currentTime;
      
    if (currentTime >= nextCycle) {
      nextCycle += period;
      
      if (currentTime > nextCycle) {
        Serial.print("Behind Cycles by: ");
        Serial.println(currentTime - nextCycle);
      }
      
      move();
      
      Serial.print("Cycle time: ");
      Serial.println(millis() - currentTime);
    }
  }  
}

void move() {
  Serial.println("Start Move"); delay(10);
  LedSign::Clear();

  delay(period / 2);
  LedSign::Clear();

  Serial.println("End Move"); delay(10); 
}


void newGame() {
 Serial.println("Starting New Game.");
 
 writeText("!%$@(#*$&");
 
 nextCycle = -1;
 run = true; 
}

void writeText(char* message) {  
  int startX = SCR_RIGHT;
  int x;
  
  do {
   x = startX;
   
    LedSign::Clear();
    for (int letter=0; message[letter] != '\0'; letter++) {
     
       x += Letters::draw(message[letter], x, 1);
       x++;
      //Jump out when we're drawing off-screen
       if (x > SCR_RIGHT)
         break;
    }

    startX--;
    delay(60);
   
  } while(x > 0);
  
}

