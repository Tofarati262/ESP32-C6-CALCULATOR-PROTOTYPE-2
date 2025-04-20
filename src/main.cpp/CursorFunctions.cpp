#include "CursorFunctions.h"
#include "iostream"
#include "DisplayInit.h"  // Ensure the correct path
#include <vector>

int cursorIndex= 0;
int cursorPos = 3;
int xPos= 3;

int lastcursorPos = 0;
bool cursorVisible = true;  // Blinking state
unsigned long lastBlinkTime = 0;

int previousmapped = 0;

int *screenendptr = &screencount;
int screenstart = 0;

void cursorMoveForward()
{
    lastcursorPos = cursorPos; //last pos is set to current pos
    tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);//removes the previous cursor
    

    cursorPos += 7;
    cursorIndex +=1;  //decreases the cursor's index 
    std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
  
}


void cursorMoveback(){
    lastcursorPos = cursorPos; //last pos is set to currentpos
    tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE); // erase the last cursors pos
    //if cursorIndex = ( decrease cursorpos by 2 or 3 if the second number is n or g
    std::cout<< "This is the cursor index before condition: "<< cursorIndex <<"\n";


      cursorPos -= 7;
      cursorIndex-=1;  //decreases the cursor's index 
      std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
       
}


void cursorDelete()
{
  lastcursorPos = cursorPos; //last pos is set to currentpos
  tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE); // erase the last cursors pos
  //if cursorIndex = ( decrease cursorpos by 2 or 3 if the second number is n or g
  std::cout<< "This is the cursor index before condition: "<< cursorIndex <<"\n";

  
  std::cout<< equationbuffer[cursorIndex] << std::endl;
  if(cursorIndex != equationbuffer.size())
  {
    equationbuffer.erase(equationbuffer.begin()+ cursorIndex);
    std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
  }
}   
