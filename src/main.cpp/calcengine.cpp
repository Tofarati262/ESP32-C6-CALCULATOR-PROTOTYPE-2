#include "CursorFunctions.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "iostream"
#include "ArithmeticStack.h"
#include <vector>
#include "calcBuffer.h"

bool calcenginerun = false;
bool calcresult = false;
bool *calcresultptr = &calcresult; 
bool rightbracket = true;
int equationcounter = 0 ;
std::vector<char>equationbuffer;  // Stores the equation input
int equationLength = 0;  // Tracks how many characters have been entered
CALCSTACK calculator;
calcBuffer memorybuffer;

int ypos = 5;

void drawCursor() { //blinks the cursor
  if (cursorVisible) {
    tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_BLACK);
  } else {
    tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
  }
}

void updateScreen() {
  tft.fillRect(0, 0, 160, 14, ST7735_WHITE);  // Clear equation display area
  
  xPos = 3;  // Reset xPos before drawing characters to the start of the screen 

  for (int i = screenstart; i < equationbuffer.size() && i < screenstart + MAX_CHARS; i++) { //prints equation from start of the screen to the end of the screen
    tft.setCursor(xPos, ypos);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
    tft.print(equationbuffer[i]);
    xPos += 7; //increase the position then printing a number at the next position
  }
  drawCursor();
}

void reinitcalcstack()
{
  calculator = CALCSTACK();
}
   
void displayanswer()
{
  int screenanswer = memorybuffer.answer();
  tft.setCursor(145, ypos+15);
  tft.setTextSize(1);
  tft.print(screenanswer);
}


void calcrun(){
  tft.fillScreen(ST7735_WHITE);
  tft.drawRect(0, 0, 160, 14, ST7735_WHITE);  // Input box
  tft.drawRect(0, 30, 160, 1, ST7735_WHITE);  // Margin

  while (true) 
  {
      
    char key = loopy();  // Get key input
    unsigned long currentMillis = millis();
    int potValue = analogRead(potPin);
    // Blink cursor every CURSOR_BLINK_DELAY ms

    if (currentMillis - lastBlinkTime >= CURSOR_BLINK_DELAY) {
      cursorVisible = !cursorVisible;
      drawCursor();
      lastBlinkTime = currentMillis;
    }
    
    //Maps Potentiometer Value

    if (potValue < minPotValue) {
      mappedValue = 0;
    } else {
      mappedValue = map(potValue, 500, 4095, 0, 500);
    }
    int speedchange = mappedValue - previousmapped;
    previousmapped = mappedValue;
    //std::cout<<"This is the degreeChange: "<< speedchange <<std::endl;

    // Move cursor only within the valid range
    /*if (speedchange > 5 && cursorIndex < equationbuffer.size() && (cursorPos + 7) < 153) {  //checks if the potentiometer changes in the positive direction and the cursor's index is less than equation length an cursor positoin is not at the screen edge
        cursorMoveForward();
        drawCursor();// draws the cursor
        updateScreen(); // updates the screen and writes the equation inside the buffer
    } else if (speedchange < -10  && cursorIndex > 0) {
        cursorMoveback();
        drawCursor(); //draw new cursor position
        updateScreen(); //print the equation on the screen
    }*/

    HandleKeys(key);
  }
}

void HandleKeys(char key)
{

  if(key == 'B' && cursorIndex > 0)
  {   // deletes the characters and updates the screen
          //cursorDelete(); //backspace needs to 
          //reduce the cursor index and decrement the cursorpos all done in the called function
          cursorMoveback();
          drawCursor(); //draw new cursor position
          updateScreen(); //print the equation on the screen
  }

  if (key == 'D' && !equationbuffer.empty())
      {
          cursorDelete(); //deletes the characters in the memory buffer
          drawCursor();// visually moves the cursor back
          updateScreen(); // updates the screen 
      }

      if(key == 'E'){ // erase the characters inside the vector 
        equationbuffer.clear();
          xPos = 3;
          cursorIndex = 0;
            cursorPos = 3;
          drawCursor(); //draw new cursor position
          updateScreen(); //print out the empty screen
  }
      
  if(key == 'L'){ //ln(
          char temp[] = {'l','n','('};
          if(equationbuffer.size()==0){ // if its at zero
              equationbuffer.push_back(temp[0]);
              cursorIndex++;
              equationbuffer.push_back(temp[1]);
              cursorIndex++;
              equationbuffer.push_back(temp[2]);
              cursorIndex++;
          }else{ //if the eqautionbuffersize is not at zero
            for(int i =0; i < 3 ; i++){
                equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
                cursorIndex++;
            }
          }
        

          lastcursorPos = cursorPos;
          tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
          std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
          cursorPos+= 21;
          drawCursor();
          updateScreen();
  }

      
  if(key == 'l'){ //log(
          lastcursorPos = cursorPos;
          tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
          cursorPos+= 28;
          char temp[]= {'l','o','g', '('};
          if(equationbuffer.size()==0){ // if its at zero
              equationbuffer.push_back(temp[0]);
              cursorIndex++;
              equationbuffer.push_back(temp[1]);
              cursorIndex++;
              equationbuffer.push_back(temp[2]);
              cursorIndex++;
              equationbuffer.push_back(temp[3]);
              cursorIndex++;
          }else{ //if the eqautionbuffersize is not at zero
            for(int i =0; i < 4 ; i++){
              equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
              cursorIndex++;
            }
          }


          std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
          drawCursor();
          updateScreen();
  }


  if(key == 'Q'){ //log(
          lastcursorPos = cursorPos;
          tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
          cursorPos+= 35;
          char temp[]= {'s','q','r', 't','('};
          if(equationbuffer.size()==0){ // if its at zero
              equationbuffer.push_back(temp[0]);
              cursorIndex++;
              equationbuffer.push_back(temp[1]);
              cursorIndex++;
              equationbuffer.push_back(temp[2]);
              cursorIndex++;
              equationbuffer.push_back(temp[3]);
              cursorIndex++;
              equationbuffer.push_back(temp[4]);
              cursorIndex++;
          }else{ //if the eqautionbuffersize is not at zero
            for(int i =0; i < 6 ; i++){
              equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
              cursorIndex++;
            }
          }


          std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
          drawCursor();
          updateScreen();
  }

  if(key == 's'){ //log(
          lastcursorPos = cursorPos;
          tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
          cursorPos+= 28;
          char temp[]= {'s','i','n','('};
          if(equationbuffer.size()==0){ // if its at zero
              equationbuffer.push_back(temp[0]);
              cursorIndex++;
              equationbuffer.push_back(temp[1]);
              cursorIndex++;
              equationbuffer.push_back(temp[2]);
              cursorIndex++;
              equationbuffer.push_back(temp[3]);
              cursorIndex++;
          }else{ //if the eqautionbuffersize is not at zero
            for(int i =0; i < 4 ; i++){
              equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
              cursorIndex++;
            }
          }


          std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
          drawCursor();
          updateScreen();
  }

  if(key == 'c'){ //log(
    lastcursorPos = cursorPos;
    tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
    cursorPos+= 28;
    char temp[]= {'c','o','s','('};
    if(equationbuffer.size()==0){ // if its at zero
      equationbuffer.push_back(temp[0]);
      cursorIndex++;
      equationbuffer.push_back(temp[1]);
      cursorIndex++;
      equationbuffer.push_back(temp[2]);
      cursorIndex++;
      equationbuffer.push_back(temp[3]);
      cursorIndex++;
    }else{ //if the eqautionbuffersize is not at zero
      for(int i =0; i < 4 ; i++){
        equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
        cursorIndex++;
      }
    }


    std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
    drawCursor();
    updateScreen();
  }

  if(key == 't'){ //log(
    lastcursorPos = cursorPos;
    tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
    cursorPos+= 28;
    char temp[]= {'t','a','n','('};
    if(equationbuffer.size()==0){ // if its at zero
      equationbuffer.push_back(temp[0]);
      cursorIndex++;
      equationbuffer.push_back(temp[1]);
      cursorIndex++;
      equationbuffer.push_back(temp[2]);
      cursorIndex++;
      equationbuffer.push_back(temp[3]);
      cursorIndex++;
    }else{ //if the eqautionbuffersize is not at zero
      for(int i =0; i < 4 ; i++){
        equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
        cursorIndex++;
      }
    }


    std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
    drawCursor();
    updateScreen();
  }
  
  if(key == 'F'&& !equationbuffer.empty() && cursorIndex < equationbuffer.size()){
      cursorMoveForward();
      drawCursor(); //draw new cursor position
      updateScreen(); //print the equation on the screen
  }
      
  if(key == '^'){
      lastcursorPos = cursorPos;
      cursorPos+= 14;
      char temp[]= {'^','('};
      if(equationbuffer.size()==0){ // if its at zero
          equationbuffer.push_back(temp[0]);
          cursorIndex++;
          equationbuffer.push_back(temp[1]);
          cursorIndex++;
      }else{ //if the eqautionbuffersize is not at zero
        for(int i =0; i != 2 ; i++){
          equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
          cursorIndex++;
        }
      }
      std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
      drawCursor();
      updateScreen();
  }

  if(key == '=' && !equationbuffer.empty())
  {
    int temp_num_count = 0;
    int temp_operator_count = 0;

    for(char number : equationbuffer)
    {
    std::cout<< number<< std::endl;
    }

    for(char value : equationbuffer)
    {
      if(value >= '0' && value <= '9')
      {
        calculator.pushNumber(value-'0');
        temp_num_count++;
        std::cout <<"Pushed number:"  << value << "\n";
      }
      if (calculator.isOperator(value) == true)
      { 
        if(calculator.isOperatorEmpty() == true)
        {
          calculator.pushOperator(value);
          temp_operator_count++;
          std::cout << "Pushed operator: "<< value << "\n";
        }else if(calculator.isOperatorEmpty() == false)
        {
          if(calculator.precedence(value) > calculator.precedence(calculator.peekOperator()))
          {
            calculator.pushOperator(value);
            temp_operator_count++;
            std::cout << "Pushed operator: "<< value << "\n";
          }else if (calculator.precedence(value) <= calculator.precedence(calculator.peekOperator()))
          {
            calculator.evaluate();
            temp_operator_count = 0; //reset the operator count 
            temp_num_count      = 0; //reset the number count 
            std::cout << "evalauted :" << calculator.peekNumber() << "\n";
            calculator.pushOperator(value);
          }
        }
      }
    }

    //error handling 
    if(temp_num_count == 0){
      std::cout << "Error : Syntax" << std::endl;
    }else if(temp_num_count == temp_operator_count)
    {
      std::cout << "Error : Syntax" << std::endl;
    }else{
      while(calculator.isEmpty() > 1){
        calculator.evaluate();
      }
      int answer = calculator.peekNumber(); 
      std::cout << answer << std::endl;
      equationcounter++; // equation count increases 
      memorybuffer.pushequation(equationbuffer,answer);
      displayanswer();
      newequation(); //creates a new equation margin
    }
  }

  if (key != 'z' && key != 'm' && key != 'Q' && key !='B' && key !='^' && key != 'E' && key != 'a' && key != 's' && key != 'c' && key != 't' && key != '=' && key != 'l'&& key!='L'&& key != 'T'&& key != 'F' && key != 'D') {
      // Replace character at current cursor position
    if(cursorIndex >=equationbuffer.size()){
      equationbuffer.push_back(key);
    }else{
      equationbuffer.at(cursorIndex) = key;
    }

    if ((cursorPos + 7) < 155 && cursorIndex < equationbuffer.size()) {
      cursorPos += 7;
      cursorIndex++;
    }
    if(cursorPos == 150 && cursorIndex < equationbuffer.size())
    {
      cursorIndex++;  //increase the cursor index this allow us to print a key to the buffer once at the edge of the screen
    }
    // Scroll screen if necessary
    if (equationLength > MAX_CHARS) {
      screenstart++;
      std::cout <<"This is the screenstart : "<< screenstart <<std::endl;
    }

    std::cout <<"This is the pos: "<<cursorPos <<std::endl;
    std::cout <<"This is the equationlength: " <<equationLength <<std::endl;
    std::cout <<"This is the index: "<<cursorIndex <<std::endl;

    // Increase equation length only if adding at the end

    // Move cursor forward (prevent going off-screen)


    //if the cursor position is at the  and the index is less than the equation length 



    updateScreen();
      drawCursor();
  }
}

void newequation()
{
  reinitcalcstack();
  int marginindex = 3;

  while(marginindex != 160)
  {
    tft.setCursor(marginindex, ypos + 18);
    tft.print('-');
    marginindex += 7;
  }

  ypos+=20;
}