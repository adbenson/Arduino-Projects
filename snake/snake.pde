#include <Charliplexing.h>

#define MAX_LENGTH 254
#define STARTX 7
#define STARTY 4
#define STARTDIR 'l'
#define TOP 0
#define LEFT 0
#define RIGHT 13
#define BOTTOM 8
#define MOVETIME 250
#define FOODBLINK 200

int head, tail;
int snake[MAX_LENGTH+1][2];
int food[2];
long nextMove;
char dir;
boolean run = false;
int blinkState;
int nextBlink;

void setup() {
  LedSign::Init();  
  
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  for (int i=14; i<20; i++) {
     pinMode(i, INPUT);
     digitalWrite(i, HIGH); 
  }
  
  newGame();
}

void newGame() {
  
  for (int i=0; i <= MAX_LENGTH; i++) {
     snake[i][0] = 0;
      snake[i][1] = 0; 
  }  
  
  head = 1;
  tail = 1;
  dir = STARTDIR;
  snake[head][0] = STARTX;
  snake[head][1] = STARTY; 
  LedSign::Clear();  
  
  newFood();
  nextMove = nextBlink = -1;
  blinkState = 1;
  run = true;
}

void loop() {
 if (run) {
   long currentTime = millis();
   if (nextMove == -1)
     nextMove = currentTime;
   if (nextBlink == -1)
     nextBlink = currentTime;
   Serial.println("loop start");
   
  for (int i=14; i<20; i++) {
     if (digitalRead(i) == LOW) {
         Serial.print("Button Down: ");
         Serial.println(i);
         
         switch(i) {
           case 16: dir = 'r';
             break;
           case 17: dir = 'l';
            break;
           case 18: dir = 'd';
            break;
           case 19: dir = 'u';
            break;
           default: Serial.print("Unknown button: "); Serial.println(i); 
         }
         
     }
  }   
   
   if (currentTime >= nextMove) {
     move();
     nextMove += MOVETIME;
     while (currentTime > nextMove) {
       nextMove += MOVETIME;
       Serial.print("Move Dropped: "); 
       Serial.println(5, DEC);
     }
   }
   
   if (currentTime >= nextBlink) {
    LedSign::Set(food[0], food[1], blinkState);
    nextBlink += FOODBLINK;
    blinkState = !blinkState; 
   }   
     
   Serial.println("loop end");
 }
}

void move() {
  Serial.println("Moving");
  int newHead = head - 1;
  if (newHead < 0)
    newHead = MAX_LENGTH;
    
  snake[newHead][0] = snake[head][0];
  snake[newHead][1] = snake[head][1];
  head = newHead;
  
  //Based on the direction, move the new head.
  if (dir == 'u')
    snake[head][1]--;
  if (dir == 'd')
    snake[head][1]++;
  if (dir == 'l')
    snake[head][0]--;
  if (dir == 'r')
    snake[head][0]++;
    
  Serial.println("Boundary check");
  if ((snake[head][0] < LEFT  || snake[head][0] > RIGHT) ||
      (snake[head][1] < TOP || snake[head][1] > BOTTOM))
      endGame(false);

  if (snake[head][0] == food[0] && snake[head][1] == food[1]) {
    if (tail == head)
      endGame(true);
      
    newFood();
  }
  else {
     LedSign::Set(snake[head][0], snake[head][1], 1);
     LedSign::Set(snake[tail][0], snake[tail][1], 0);
     tail--;
     if (tail < 0)
       tail = MAX_LENGTH;
  }
  
  Serial.println("Collision test");
  int test = head;
  while(test != tail) {
      test++;
     if (test > MAX_LENGTH)
       test = 0;
       
     if (snake[head][0] == snake[test][0] && snake[head][1] == snake[test][1])
       endGame(false);
  }
  
  Serial.println("End Move.");
}

void newFood() {
  Serial.println("Placing food");
  boolean foodGood;
  do {    
      food[0] = random(LEFT, RIGHT+1);
      food[1] = random(TOP, BOTTOM+1);
      
      Serial.print("Trying ");
      Serial.print(food[0]);
      Serial.print(", ");
      Serial.println(food[1]);
      
      foodGood = true;
  
      int test = head - 1;
      do {
        
        test++;
        if (test > MAX_LENGTH)
         test = 0; 
         
        if (food[0] == snake[test][0] && food[1] == snake[test][1])
          ;//foodGood = false;
        
      
      } while (test != tail && foodGood);
      
    } while (!foodGood);
    Serial.println("Food placed.");
   
    blinkState = 1;
    nextBlink = -1;
    LedSign::Set(food[0], food[1], 1);
}

void endGame(boolean won) {
  run = false;
  
  LedSign::Clear();
 
  if (won) {
    int xOffset = 1;
//    xOffset = Font::Draw('W', xOffset, 0, 1);
//    xOffset = Font::Draw('I', xOffset, 0, 1);
//    Font::Draw('N', xOffset, 0, 1);
    Serial.println("Game Won");
  }
  else {
    //printMessage();
    Serial.println("Game Lost");
  }
 
 delay(3000); 

  newGame();
}

void printMessage() {
  
char test[]="HELLO WORLD!";

    int8_t x=0,x2=0;
  for(int8_t j=13;j>-100;j--) {
    x=j;
    LedSign::Clear();
    for(int i=0;i<17;i++) {
     // x2=Font::Draw(test[i],x,0);
      x+=x2;
      if (x>=13) break;
    }  
    delay(80);
  }
}

