/*
  TEXT SAMPLE CODE for LOL Shield for Arduino
  Copyright 2009/2010 Benjamin Sonntag <benjamin@sonntag.fr> http://benjamin.sonntag.fr/
  
  History:
  	2009-12-31 - V1.0 FONT Drawing, at Berlin after 26C3 ;) 

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.
*/

#include "Charliplexing.h"
#include "Font.h"

#include "WProgram.h"


  char test[]="XXXXXXXXXXXXX";
  int8_t testLength = 13;
  
  int scrollDelay;
  int scrollSpeed = 20;


/* -----------------------------------------------------------------  */
/** MAIN program Setup
 */
void setup()                    // run once, when the sketch starts
{
  LedSign::Init();
  
  scrollDelay = 1000 / scrollSpeed;
}


/* -----------------------------------------------------------------  */
/** MAIN program Loop
 */
void loop()                     // run over and over again
{



  int8_t letterOffset = 0;
  int8_t initOffset = 13;
  
  do {
    letterOffset = initOffset--;
    
    LedSign::Clear();
    //For each letter in the test string
    for(int letter = 0; letter < testLength; letter++) {
      //Draw the letter and capture its width
      letterOffset += Font::Draw(test[letter], letterOffset, 0);
 
      if (letterOffset >= 13)
        break;
    }
    
    delay(scrollDelay);    
    
  } while (initOffset > -100);
  
  delay(1000);
}


