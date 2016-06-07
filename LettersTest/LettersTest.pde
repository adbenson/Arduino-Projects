
#include <Charliplexing.h>

#define MIN_LETTER 32
#define MAX_LETTER 126
  
  class Letter {
  public:
    char character;
    int  ascii;
    byte* pixels;
    int  pixelCount;  
    int  size;
};

byte xpix[] = {7,0, 4,0, 1,1, 3,1, 2,2, 2,3, 1,4, 3,4, 0,5, 4,5};
byte wpix[] = {7,0, 4,0, 0,1, 4,1, 0,2, 4,2, 0,3, 4,3, 0,4, 2,4, 4,4, 1,5, 3,5};

Letter letterSet[] = {
{ 'W' , 87, ((byte[]){0,0, 4,0, 0,1, 4,1, 0,2, 4,2, 0,3, 4,3, 0,4, 2,4, 4,4, 1,5, 3,5}), 13, 5 }, 	//W
{ 'X' , 88, (byte[20]){0,0, 4,0, 1,1, 3,1, 2,2, 2,3, 1,4, 3,4, 0,5, 4,5}, 10, 5 } 	//X
}; //end letterSet[]

void loop() {}

void setup() {
  LedSign::Init();
  LedSign::Clear();

	Letter X = letterSet[0];
	int x, y, value;
	x = y = value = 1;
	
	Serial.begin(9600);
	Serial.print("Printing: '");
	Serial.print(X.character);
	Serial.print("' - ");
	Serial.print(X.pixelCount);
	Serial.println(" pixels.");
Serial.println((int)*(wpix), HEX); Serial.println("-");
Serial.println((int)&(X.character), HEX); Serial.println("-");
Serial.println((int)&(X.ascii), HEX); Serial.println("-");
Serial.println((int)(X.pixels), HEX); Serial.println("-");
Serial.println((int)&(X.pixelCount), HEX); Serial.println("-");
Serial.println((int)&(X.size), HEX); Serial.println("-");


byte* p = X.pixels;
for (int i=0; i<26; i++) {
   Serial.print(p[i], HEX);
   Serial.print(" ");
}
Serial.println();
for (int i=0; i<26; i++) {
  Serial.print((byte)wpix[i], HEX);
     Serial.print(" ");
}
Serial.println();

	for (int pixel=0; pixel<X.pixelCount; pixel++) {
		int i = pixel*2;
		int xOffset = x + X.pixels[i];
		int yOffset = y + X.pixels[i+1];
		Serial.print(pixel);
		Serial.print(": ");
		Serial.print("(");
		Serial.print(i);
		Serial.print(")");
		Serial.print(X.pixels[i], DEC);
		Serial.print(", ");
		Serial.println(X.pixels[i+1], DEC);
		LedSign::Set(xOffset, yOffset, value);
	}

delay(3000);
}

int draw(char letter, int x, int y, int value) {
	if (letter < MIN_LETTER || letter > MAX_LETTER)
		return 0;

	if (letter == ' ')
		return 3;

	Letter toDraw = letterSet[letter - MIN_LETTER];

	for (int pixel=0; pixel<toDraw.pixelCount; pixel++) {
		int i = pixel*2;
		int xOffset = x + toDraw.pixels[i];
		int yOffset = y + toDraw.pixels[i+1];
		LedSign::Set(xOffset, yOffset, value);
	}

	return toDraw.size;
}

int messageWidth(char* message) {

	for (int i=0; message[i] != '\0'; i++) {
	
	}
  
}


