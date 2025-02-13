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
    
    if(equationbuffer.at(cursorIndex) == 'l'){//if cursorIndex = l increase cursorpos by 2 or 3 if the second number is n or o 
      if(equationbuffer.at(cursorIndex+1) == 'n'){


        cursorPos += 21;
        cursorIndex+=3;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;


      }else if(equationbuffer.at(cursorIndex+1) == '0'){

        cursorPos+=35;
        cursorIndex+=5;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;


      }

    }else{
      
      cursorPos += 7;  //increments the cursoposition
      cursorIndex++;  //increases the cursor's index 
      std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;

    }
}


void cursorMoveback(){
    lastcursorPos = cursorPos; //last pos is set to currentpos
    tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE); // erase the last cursors pos
    //if cursorIndex = ( decrease cursorpos by 2 or 3 if the second number is n or g
    if((equationbuffer.at(cursorIndex) == '(' && equationbuffer.at(cursorIndex-1)== 'n')||(equationbuffer.at(cursorIndex) == '(' && equationbuffer.at(cursorIndex-1)== 'g')){
      if(equationbuffer.at(cursorIndex-1) == 'n'){
        cursorPos -= 21;
        cursorIndex-=3;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer.at(cursorIndex-1) == 'g'){
        cursorPos-=35;
        cursorIndex-=5;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else{
      cursorPos -= 7; //decrement the current cursor pos moving it backward
      cursorIndex--; //decrease the cursors index
      std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl; 
    }

    if(cursorIndex < screenstart) // decreases the screen start index once the cursor moves back to zero and screenstart will be at 1 
    {
      std::cout <<"This is the screenstart : "<<screenstart <<std::endl;
      screenstart--; //decreases the screenstart and it shows the start of the equation that wasnot in the view scope
    }
}