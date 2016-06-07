#include <Charliplexing.h>
#include <Figure.h>
#include <Font.h>

#define BTN_UP 19
#define BTN_DOWN 18
#define BTN_LEFT 17
#define BTN_RIGHT 16

int buttons[] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT};
int buttonCount = 4;

void setup() {
 LedSign::Init();
 
  for (int i=0; i<buttonCount; i++) {
     pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
}

void loop() {
  for (int i=0; i<buttonCount; i++) {
     int val = digitalRead(buttons[i]);
     LedSign::Set(3+i, 4, val);
  }
  
}
