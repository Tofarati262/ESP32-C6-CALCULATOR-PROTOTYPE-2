#include "CursorFunctions.h"
#include "iostream"
#include "DisplayInit.h"  // Ensure the correct path

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
    cursorPos += 7;  //increments the cursoposition
    cursorIndex++;  //increases the cursor's index 
    std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
}


void cursorMoveback(){
    lastcursorPos = cursorPos; //last pos is set to currentpos
    cursorPos -= 7; //decrement the current cursor pos moving it backward
    tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE); // erase the last cursors pos
    cursorIndex--; //decrease the cursors index
     std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl; 
    if(cursorIndex < screenstart) // decreases the screen start index once the cursor moves back to zero and screenstart will be at 1 
    {
      std::cout <<"This is the screenstart : "<<screenstart <<std::endl;
      screenstart--; //decreases the screenstart and it shows the start of the equation that wasnot in the view scope
    }
}