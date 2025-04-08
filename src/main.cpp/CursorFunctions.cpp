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


      }else if(equationbuffer.at(cursorIndex+1) == 'o'){

        cursorPos+=28;
        cursorIndex+=4;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;


      }
    }else if (equationbuffer.at(cursorIndex) == 'c'){//cos
      if(equationbuffer.at(cursorIndex+1) == 'o'){
        cursorPos += 28;
        cursorIndex+=4;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else if (equationbuffer.at(cursorIndex) == 't'){//tan
      if(equationbuffer.at(cursorIndex+1) == 'a'){
        cursorPos += 28;
        cursorIndex+=4;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else if (equationbuffer.at(cursorIndex) == 's'){ //sqrt and sin

      if(equationbuffer.at(cursorIndex+1) == 'q'){
        cursorPos += 35;
        cursorIndex+=5;  //increases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }

      if(equationbuffer.at(cursorIndex+1) == 'i'){
        cursorPos += 28;
        cursorIndex+=4;  //increases the cursor's index 
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
    std::cout<< "This is the cursor index before condition: "<< cursorIndex <<"\n";

    if(equationbuffer[cursorIndex] == '('){
      if(equationbuffer.at(cursorIndex-1) == 'n'){
        cursorPos -= 14;
        cursorIndex-=2;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer.at(cursorIndex-1) == 'g'){
        cursorPos-=21;
        cursorIndex-=3;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;

      }else if(equationbuffer.at(cursorIndex-1) == 't'){
        cursorPos-=28;
        cursorIndex-=4;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if (equationbuffer.at(cursorIndex-1) == 's'){ //cos
        cursorPos -= 21;
        cursorIndex-=3;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if (equationbuffer.at(cursorIndex-2) == 'i'){ //sin
        cursorPos -= 21;
        cursorIndex-=3;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if (equationbuffer.at(cursorIndex-2) == 'a'){ //tan
        cursorPos -= 21;
        cursorIndex-=3;  //decreases the cursor's index 
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else{
        cursorPos -= 7; //decrement the current cursor pos moving it backward
        cursorIndex--; //decrease the cursors index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl; 
      }
    }else{
       cursorPos -= 7; //decrement the current cursor pos moving it backward
       cursorIndex--; //decrease the cursors index
       std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl; 
    }
       
}


void cursorDelete()
{
    lastcursorPos = cursorPos; //last pos is set to currentpos
    tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE); // erase the last cursors pos
    //if cursorIndex = ( decrease cursorpos by 2 or 3 if the second number is n or g
    std::cout<< "This is the cursor index before condition: "<< cursorIndex <<"\n";

  
   std::cout<< equationbuffer[cursorIndex] << std::endl;

    //ln or log delete

    if(equationbuffer[cursorIndex] == 'l'){ 
      if(equationbuffer[cursorIndex+1] == 'n'){
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex+1] == 'o'){
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
  
      }
    
    }else if(equationbuffer[cursorIndex] == 's'){ //sin and sqrt
      if(equationbuffer[cursorIndex+1] == 'q'){
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+4); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex+1] == 'i'){ 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      } 
    }else if (equationbuffer[cursorIndex] == 't'){  //tan
      if(equationbuffer[cursorIndex+1] == 'a'){
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else if (equationbuffer[cursorIndex] == 'c'){ //cos
      if(equationbuffer[cursorIndex+1] == 'o'){
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex+1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else if(equationbuffer[cursorIndex] == '('){
      if(equationbuffer[cursorIndex-1] == 'n'){ //ln
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex-1] == 'g'){ //log
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
  
      }else if(equationbuffer[cursorIndex-1] == 't'){ //sqrt
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-4); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex-1] == 's'){ //cos(
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex-2] == 'i'){ //sin(
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }else if(equationbuffer[cursorIndex-2] == 'a'){ //tan(
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-3); // the number at the cursor index 
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-2); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index
        equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index
        std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      }
    }else{
      equationbuffer.erase(equationbuffer.begin()+cursorIndex-1); // the number at the cursor index 
      std::cout <<"This is the cursor index: "<< cursorIndex <<std::endl; 
    }
}   
