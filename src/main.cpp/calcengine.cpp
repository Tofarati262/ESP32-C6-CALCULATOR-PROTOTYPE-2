#include "CursorFunctions.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "iostream"
#include <string>
#include "ArithmeticStack.h"
#include <vector>
#include "calcBuffer.h"
#include "CALCERROR.h"

bool calcenginerun = false;
bool calcresult = false;
bool *calcresultptr = &calcresult; 
bool rightbracket = true;
int equationcounter = 0 ;
std::vector<char>equationbuffer;  // Stores the equation input
int equationLength = 0;  // Tracks how many characters have been entered
CALCSTACK calculator;
calcBuffer memorybuffer;
Error err;

int ypos = 5;

void drawCursor() { //blinks the cursor
  if (cursorVisible) {
    tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_BLACK);
  } else {
    tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
  }
}

void updateScreen() {
  tft.fillRect(0, ypos, 160, 14, ST7735_WHITE);  // Clear equation display area
  
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

void displayanswer()
{

  double answers = memorybuffer.answer();
  std::string  screenanswer = std::to_string(answers);
  int length = screenanswer.length();
  
  tft.setCursor(155- length - 4  * 7, ypos+15);
  tft.setTextSize(1);
  tft.print(answers);
}

void displayequations()
{
  for(int i = 0; i!= equationcounter ; i++)
  {
    std::vector <char> temp = memorybuffer.getEquation(i);

    tft.fillRect(0, 5 + (40 * i), 160, 14, ST7735_WHITE);  // Clear equation display area
  
    int tempxPos = 3;  // Reset xPos before drawing characters to the start of the screen 

    for (int j = screenstart; j < temp.size() && j < screenstart + MAX_CHARS; j++) { //prints equation from start of the screen to the end of the screen
      tft.setCursor(tempxPos, 5 + (40 * i));
      tft.setTextSize(1);
      tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
      tft.print(temp[j]);
      tempxPos += 7; //increase the position then printing a number at the next position
    }
  }
}

int drawNewMargin()
{
  if(equationcounter < 3)
  {
    int marginindex = 3;
    while(marginindex != 157)
    {
      tft.setCursor(marginindex, ypos + 30);
      tft.print('-');
      marginindex += 7;
    }
    cursorIndex = 0;
    cursorPos = 3;
    calculator = CALCSTACK();
    ypos+=40;
    equationbuffer.clear();
    updateScreen();
    if(equationcounter > 0)
    {
      displayequations();
    }
    return 1;
  }
  return 0;
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
        tft.drawRect(0, ypos, 160, 14, ST7735_WHITE);  // Input box
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
    double appendednumber = 0.0;
    bool decimalseen = false;
    double divisor = 10.0;
    temp_num_count = memorybuffer.countValues(equationbuffer).first;
    temp_operator_count = memorybuffer.countValues(equationbuffer).second;


    //scan for decimal

    vector <char> newequationbuffer = equationbuffer;

    newequationbuffer = memorybuffer.Specialfunctions(newequationbuffer);

    if(temp_num_count == 0)
    {
      err.display_error("SYNTAX");
    }else if(temp_num_count == temp_operator_count )
    {
      err.display_error("SYNTAX");
    }else if(temp_operator_count > temp_num_count )
    {
      err.display_error("SYNTAX");
    }



    for(char value : newequationbuffer)
    {
        if (value == '.') {
          decimalseen = true;
          continue;
        }


      if(value >= '0' && value <= '9')
      {

        if (!decimalseen) {
          appendednumber = appendednumber * 10 +  (value -'0');
        } else {
          appendednumber +=(value -'0') / divisor;
          divisor *= 10;
        }
        
        std::cout <<"Pushed number:"  << value << "\n";
      }

      if (calculator.isOperator(value) == true)
      { 

        calculator.pushNumber(appendednumber);
        std::cout <<"Pushed number:"  << appendednumber << "\n";
        appendednumber = 0;
        divisor = 10;
        decimalseen = false;

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
            temp_operator_count++;
          }
        }
      }
    }
    calculator.pushNumber(appendednumber);
    //error handling 
      while(calculator.isEmpty() > 1){
        calculator.evaluate();
      }

      double answer = calculator.peekNumber(); 
      std::cout << answer << std::endl;
      equationcounter++; // equation count increases 
      memorybuffer.pushequation(equationbuffer,answer);
      displayanswer(); //displays answer
      drawNewMargin(); //drawnewmargin
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
}