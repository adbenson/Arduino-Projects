#include <Charliplexing.h>

#define minX 0
#define maxX 13
#define minY 0
#define maxY 8

#define MILLIS_PER_SEC 1000
#define SECS_PER_MIN 60
#define MINS_PER_HOUR 60
#define HOURS_PER_MERID 12


#define BTN_UP 19
#define BTN_DOWN 18
#define BTN_LEFT 17
#define BTN_RIGHT 16

int buttons[] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT};
int buttonCount = 4;

const boolean printTimeOverSerial = false;


boolean AM;

int hour, minute, second;

int digitPixels[][13][2] = {
  //0
  { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, 
    {1, 0}, {1, 4},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  },
  //1
  { {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}
  },
  //2
  { {0, 0}, {0, 3}, {0, 4},
    {1, 0}, {1, 2}, {1, 4},
    {2, 1}, {2, 4}
  },
  //3
  { {0, 0}, {0, 4}, 
    {1, 0}, {1, 2}, {1, 4},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  },
  //4
  { {0, 0}, {0, 1}, {0, 2},
    {1, 2},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  },
  //5
  { {0, 0}, {0, 1}, {0, 2}, {0, 4}, 
    {1, 0}, {1, 2}, {1, 4},
    {2, 0}, {2, 2}, {2, 3},
  },
  //6
  { {0, 1}, {0, 2}, {0, 3}, {0, 4}, 
    {1, 0}, {1, 2}, {1, 4},
    {2, 0}, {2, 2}, {2, 3}, {2, 4}
  },
  //7
  { {0, 0},
    {1, 0}, {1, 3}, {1, 4},
    {2, 0}, {2, 1}, {2, 2}
  },
  //8
  { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, 
    {1, 0}, {1, 2}, {1, 4},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  },
  //9
  { {0, 0}, {0, 1}, {0, 2}, {0, 4}, 
    {1, 0}, {1, 2}, {1, 4},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}
  },
};

int digitPixelCount[10] = {
//  0   1   2   3   4   5   6   7   8   9
   12,  5,  8, 10, 11, 10, 11,  7, 13, 11 
};


void setup() {
  LedSign::Init();  //Initializes the screen
  
  drawMeridian();
  AM = true;
  hour = 12;
  minute = 0;
  second = 0;
  setMeridian(AM);
  drawHours();
  drawMinutes();
  
  for (int i=0; i<buttonCount; i++) {
     pinMode(buttons[i], INPUT);
  }
  
  Serial.begin(9600);
}

void loop() {
  
  for (int i=0; i<buttonCount; i++) {
    int btn = buttons[i];
    if (digitalRead(buttons[i]) {
      switch(btn) {
        case BTN_UP:
           hour = (++hour) %
           break;
        case BTN_DOWN:
           break;
        case BTN_LEFT:
           break;
        case BTN_RIGHT:
           break;
        default:        
      }     
    }
  }
  
  incrementSecond(1);
  
  if (printTimeOverSerial) {
    Serial.print(hour);
    if (second % 2 == 0)
      Serial.print(":");
    else
      Serial.print(" ");
      
    Serial.print(minute);
    if (AM)
      Serial.println("AM");
    else
      Serial.println("PM");
  }
    
  tick(second % 2 == 0);
  
  delay(MILLIS_PER_SEC);
}

void incrementSecond(int val) {
  second++;
  if (second >= SECS_PER_MIN) {
    second = 0;
    incrementMinute(1);
  }
  if (second < 0) {
     second = SECS_PER_MIN -1;
    incrementMinute(-1); 
  }
  drawSeconds();
}

void incrementMinute(int val) {
  minute += val;
  if (minute >= MINS_PER_HOUR) {
    minute = 0; 
    incrementHour(1);
  }
  if (minute < 0) {
    minute = MINS_PER_HOUR - 1;
    incrementHour(-1); 
  }
  drawMinutes();
}

void incrementHour(int val) {
   hour += val;
   if (hour > HOURS_PER_MERID) {
     hour = 1;
     AM = !AM;
     setMeridian(AM);   
   }
   if (hour < 1) {
     hour = HOURS_PER_MERID;
     AM = !AM;
     setMeridian(AM); 
   }
   drawHours();
}

void setMeridian(boolean AM) {
  int a = 1, p = 1;
  
  if (AM)
    p = 0;
  else
    a = 0;
  
  LedSign::Set(0, 6, p);
  LedSign::Set(2, 6, p);
  LedSign::Set(2, 8, a);
}

void drawHours() {
  int ones = hour % 10;
  boolean tens = (hour >= 10);
  
  drawDigit(3, 0, ones);
  if (hour >= 10)
    drawDigit(0, 0, 1);
  else
    clearDigit(0, 0);
}

void drawMinutes() {
  int ones = minute % 10;
  int tens = minute / 10;
  
  drawDigit(7, 0, tens);
  drawDigit(11, 0, ones);
}

void drawSeconds() {
 
 for (int x = 10; x <= maxX; x++) {
    LedSign::Set(x, 6, 0);
    LedSign::Set(x, 7, 0);
 } 
 
 //Ones
  drawSecondRow(second % 10, 7);
 //Tens
  drawSecondRow(second / 10, 6);
}

void drawSecondRow(int val, int y) {
  
  for (int power = 0; power <=4; power++)

    if (val & (1 << power))
      LedSign::Set(9 + (4-power), y, 1);
}

void drawDigit(int x, int y, int digit) {
  clearDigit(x, y);
  
  for (int pixel=0; pixel < digitPixelCount[digit]; pixel++) {
    int* pixels = digitPixels[digit][pixel];
    LedSign::Set(pixels[0] + x, pixels[1] + y, 1);
  }  
}

void clearDigit(int startX, int startY) {
 int endX = startX + 3;
 int endY = startY + 5;
  
 for (int x = startX; x < endX; x++) {
   for (int y = startY; y < endY; y++) {
    LedSign::Set(x, y, 0);     
   }
 }
}

void tick(boolean on) {
  int value = 1;
  if (!on)
    value = 0; 
    
  LedSign::Set(6, 1, value);
  LedSign::Set(6, 3, value);

}

void drawMeridian() {
  
  int AP[][2] = {
    {0, 7}, {0, 8},
    {1, 6}, {1, 7},
    {2, 7}
  };
  int apLen = 5;
  
  for (int i = 0; i < apLen; i++) {
     LedSign::Set(AP[i][0], AP[i][1], 1); 
  }
  
  int M[][2] = {
    {4, 6}, {4, 7}, {4, 8},
    {5, 6},
    {6, 7},
    {7, 6},
    {8, 6}, {8, 7}, {8, 8}
  }; 
  int mLen = 9;
  
  for (int i = 0; i < mLen; i++) {
     LedSign::Set(M[i][0], M[i][1], 1); 
  }  
}

