#ifndef Letters_h
#define Letters_h

#include "WProgram.h"

namespace Letters
{

class Letter {
  public:
	Letter();
	Letter(char character, int ascii, int* pixels, int pixelCount,int size);
    char character;
    int  ascii;
    int* pixels;
    int  pixelCount;  
    int  size;
};

int draw(char letter, int x, int y, int value = 1);

int messageWidth(char* message);

void init(int min, int max);

}

#endif