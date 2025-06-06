#include "CursorFunctions.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "iostream"
#include <string>
#include "ArithmeticStack.h"
#include <vector>
#include "calcBuffer.h"
#include "CALCERROR.h"

unsigned long lastEqualsPress = 0;
const unsigned long debounceDelay = 300; // milliseconds
int maxVisibleEquations = 3;
bool CursorEnable = true;
bool calcenginerun = false;
int equationshifter = 0;
int selectedEquationIndex = -1;
bool selectedstate = false;
int previousEquationIndex = 0;
bool calcresult = false;
bool *calcresultptr = &calcresult; 
int equationcounter = 0;
std::vector<char>equationbuffer;
int equationLength = 0;
CALCSTACK calculator;
calcBuffer memorybuffer;
Potentiometer pot3;
Error err;

int ypos = 5;

void drawCursor() {

  if(CursorEnable == true)
  {
    if (cursorVisible) {
      tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_BLACK);
    } else {
      tft.fillRect(cursorPos, ypos, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
    }
  }

}

void updateScreen() {
  tft.fillRect(0, ypos, 160, 14, ST7735_WHITE);
  xPos = 3;
  for (int i = screenstart; i < equationbuffer.size() && i < screenstart + MAX_CHARS; i++) {
    tft.setCursor(xPos, ypos);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
    tft.print(equationbuffer[i]);
    xPos += 7;
  }
  drawCursor();
}


void displayequations() {
  int displayCount = std::min(3, equationcounter - equationshifter);
  for (int i = 0; i < displayCount; i++) {
    int actualIndex = i + equationshifter;
    auto [equation, answer] = memorybuffer.getEquation(actualIndex);

    uint16_t bgColor = (actualIndex == selectedEquationIndex && selectedstate == true) ? ST7735_RED : ST7735_WHITE;
    uint16_t textColor = ST7735_BLACK;

    tft.fillRect(0, 5 + (40 * i), 160, 14, ST7735_WHITE);
    int tempxPos = 3;
    for (int j = screenstart; j < equation.size() && j < screenstart + MAX_CHARS; j++) {
      tft.setCursor(tempxPos, 5 + (40 * i));
      tft.setTextSize(1);
      tft.setTextColor(textColor, bgColor);
      tft.print(equation[j]);
      tempxPos += 7;
    }
    std::string screenanswer = std::to_string(answer);
    int length = screenanswer.length();
    tft.setCursor(155 - length - 4 * 7, (40 * i) + 20);
    tft.fillRect(105, (40 * i) + 20, 50, 11, ST7735_WHITE);
    tft.setTextColor(textColor, ST7735_WHITE);
    tft.setTextSize(1);
    tft.print(answer);
  }
}


int drawNewMargin() {
  if (equationcounter < 3) {
    int marginindex = 3;
    while (marginindex != 157) {
      tft.setCursor(marginindex, ypos + 30);
      tft.print('-');
      marginindex += 7;
    }
    cursorIndex = 0;
    cursorPos = 3;
    calculator = CALCSTACK();
    ypos += 40;
    equationbuffer.clear();
    updateScreen();
    displayequations();
    cout << "drew new margin" << "\n";
    return 1;
  } else {
    cursorIndex = 0;
    cursorPos = 3;
    calculator = CALCSTACK();
    equationbuffer.clear();
    equationshifter = equationcounter - 2;
    selectedEquationIndex = equationcounter - 1;
    updateScreen();
    displayequations();
    cout << "drew new margin" << "\n";
    return 0;
  }
}


void updateMargin()
{
 

  if(equationcounter > 0)
  {
    int refreshmarginindex = 3;
    while (refreshmarginindex != 157) {
      tft.setCursor(refreshmarginindex, 35);
      tft.print('-');
      if(equationcounter > 1)
      {
        tft.setCursor(refreshmarginindex, 75);
      tft.print('-');
      }
      refreshmarginindex += 7;
    }
  }
}


void calcrun(){
  tft.fillScreen(ST7735_WHITE);
  tft.drawRect(0, 0, 160, 14, ST7735_WHITE);  // Input box
  tft.drawRect(0, 30, 160, 1, ST7735_WHITE);  // Margin
  int prevpotValue; 
  while (true) 
  {
      
    char key = loopy();  // Get key input
    unsigned long currentMillis = millis();
    int potValue = pot3.getPotValue();


    if(selectedEquationIndex > memorybuffer.Size()-1)
    {
      CursorEnable = true;
      selectedstate = false;
    }


    if (equationcounter > 0) {
      int potValue = pot3.getPotValue();


      if (key == 'd' && selectedEquationIndex - equationshifter ==  2) {
        CursorEnable = true;
        selectedstate = false;
      }

      // Scroll down
      if (key == 'd' && selectedEquationIndex <= equationcounter - 1) {
        selectedEquationIndex++;

        std::cout << "This is the selected index: "<<selectedEquationIndex<< "\n";
        std::cout << "This is the equation shifter index: " <<equationshifter << "\n";
        // If selected is out of view at bottom, shift down
        if (selectedEquationIndex >= equationshifter + maxVisibleEquations) {
          equationshifter++;
        }

        CursorEnable = false;
        selectedstate = true;

        tft.fillRect(3,80,160,40,ST7735_WHITE);

        displayequations();
        prevpotValue = potValue;
      }

      // Scroll up
      else if (key == 'u' && selectedEquationIndex > 0) {
        selectedEquationIndex--;

        std::cout << "This is the selected index: "<<  selectedEquationIndex<< "\n";
        std::cout << "This is the equation shifter index: " <<equationshifter << "\n";

        // If selected is out of view at top, shift up
        if (selectedEquationIndex < equationshifter) {
          equationshifter--;
        }

        selectedstate = true;
        CursorEnable = false;
        displayequations();
        prevpotValue = potValue;
      }
    }


    // Blink cursor every CURSOR_BLINK_DELAY ms

    if (currentMillis - lastBlinkTime >= CURSOR_BLINK_DELAY && CursorEnable == true) {
      cursorVisible = !cursorVisible;
      drawCursor();
      lastBlinkTime = currentMillis;
    }
    
    if(CursorEnable == true){

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
            std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
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


            std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
            drawCursor();
            updateScreen();
      }

      if(key == 'Q'){ //sqrt(
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


            std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
            drawCursor();
            updateScreen();
    }

    if(key == 's'){ //sin(
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


            std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
            drawCursor();
            updateScreen();
    }

    if(key == 'c'){ //cos(
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


      std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
      drawCursor();
      updateScreen();
    }

    if(key == 't'){ //tan(
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


      std::cout <<"This is the cursor index: "<<cursorIndex <<"\n";
      drawCursor();
      updateScreen();
    }
    
    if(key == 'F'&& !equationbuffer.empty() && cursorIndex < equationbuffer.size()){
        cursorMoveForward();
        drawCursor(); //draw new cursor position
        updateScreen(); //print the equation on the screen
    }

    if (key != 'z' && key != 'm' && key != 'Q' && key !='B' && key != 'E' && key != 'a' && key != 's' && key != 'c' && key != 't' && key != '=' && key != 'l'&& key!='L'&& key != 'T'&& key != 'F' && key != 'D' && key != 'd' && key != 'u') 
    {
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
        std::cout <<"This is the screenstart : "<< screenstart <<"\n";
      }

      std::cout <<"This is the pos: "<<cursorPos <<"\n";
      std::cout <<"This is the equationlength: " <<equationLength <<"\n";
      std::cout <<"This is the index: "<<cursorIndex <<"\n";

      // Increase equation length only if adding at the end

      // Move cursor forward (prevent going off-screen)


      //if the cursor position is at the  and the index is less than the equation length 

      if(CursorEnable == true)
      {
        drawCursor();
      }

       updateScreen();
    }
 

  }

    if(key == '=' && !equationbuffer.empty() && equationcounter < 20)
    {

      using namespace std;
      unsigned long currentTime = millis();
      if (currentTime - lastEqualsPress > debounceDelay) {
        lastEqualsPress = currentTime;
        int temp_num_count = 0;
        int temp_operator_count = 0;
        bool decimalseen = false;
        double divisor = 10.0;

        temp_num_count = memorybuffer.countValues(equationbuffer).first;
        temp_operator_count = memorybuffer.countValues(equationbuffer).second;


        //scan for decimal

        std::cout<< "This is the number count : " << temp_num_count << "\n";
        std::cout<< "This is the operator count : " << temp_operator_count << "\n";

        if(err.findErrors(temp_num_count, temp_operator_count, equationbuffer) == false)
        {

          
          
          vector <char> newequationbuffer = equationbuffer;

          //scans for special functions and calculates their values then appends them to the equation
          newequationbuffer = memorybuffer.Specialfunctions(newequationbuffer);

          std::string status(newequationbuffer.begin(), newequationbuffer.end());

          if(status == "error")
          {

            std::cout << "Found errors" << "\n";

            updateScreen();
            updateMargin();
            displayequations();
            continue;
          }else{

            std::cout << "Did not find any errors" << "\n";
            
            std::cout << "This is the size of the equation: "<< newequationbuffer.size() << "\n";

            std::string appendednumber = "";

            for(int i = 0 ; i < newequationbuffer.size(); i++)
            {
              char ch = newequationbuffer[i];

              if(newequationbuffer[i] == '-' && (i == 0 || newequationbuffer[i-1] == '('))
              {
                appendednumber = "-";
                int j = i + 1;

                while(j < newequationbuffer.size())
                {
                  char next_ch = newequationbuffer[j];
                  if((next_ch >= '0' && next_ch <= '9') || next_ch == '.')
                  {
                    appendednumber += next_ch;
                    j++;
                  }else{
                    break;
                  }             
                }

                i = j - 1;

                cout << "This is the value after the loop: " << newequationbuffer[i] << "\n";
                calculator.pushNumber(memorybuffer.StringToDouble(appendednumber));
                cout << "This is the appended number : " << appendednumber << "\n";
                appendednumber = "";

              }
              
              else if ((newequationbuffer[i] >= '0'&&  newequationbuffer[i]  <= '9') || newequationbuffer[i] == '.')
              {
                int j = i;
                appendednumber = "";

                while(j < newequationbuffer.size())
                {
                  char temp_ch = newequationbuffer[j];
                  if((temp_ch >= '0' && temp_ch <= '9') || temp_ch == '.')
                  {
                    appendednumber += temp_ch;
                    j++;
                  }else{
                    break;
                  }
                }
              
                i = j - 1;
                cout << "This is the value after the loop: " << newequationbuffer[i] << "\n";
                calculator.pushNumber(memorybuffer.StringToDouble(appendednumber));                
                std::cout << "This is the appended number : "  << appendednumber << "\n"; // converts string to double then pushes the number to the stack

                appendednumber = "";


              }else if(ch == '(')
              {
                calculator.pushOperator(ch); // pushes the opening parenthesis to the operator stack 
              }else if (ch == ')')
              {
                while(calculator.isOperatorEmpty()==false && calculator.peekOperator() != '(')
                {
                  calculator.evaluate(); // evaluate numbers in the stack when the closing bracket is not found 
                }

                if(calculator.isOperatorEmpty() == false && calculator.peekOperator() == '(')  //pops the  opening bracket when it is found 
                {
                  calculator.popOperator();
                }
              }
              else if(calculator.isOperator(ch) == true) // finds an operator 
              {
                calculator.pushOperator(ch); // then pushes the less significant operator 

                std::cout << "This is the pushed operator  : "  << ch << "\n"; // converts string to double then pushes the number to the stack
              }
            }   

            
            while(calculator.isEmpty() > 1){
              calculator.evaluate();
            }

            double answer = calculator.peekNumber(); 
            equationcounter++;                                               // equation count increases 
            memorybuffer.pushequation(equationbuffer,answer);
            drawNewMargin();                                              //drawnewmargin
            std::cout << "evaluated the answer" << answer << "\n";
            
          }
        }else{
          updateScreen();
          updateMargin();
          displayequations();
        }
      }

    
    }
  }
}

/*
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

            if(value == '(')
            {
              decimalseen = false;
              calculator.pushOperator(value);
            }

            if(value == ')')
            {
              decimalseen = false;
              while (calculator.isOperatorEmpty() == false && calculator.peekOperator() != '(')
              {
                calculator.evaluate();
              }
              if(calculator.isOperatorEmpty() == false)
              {
                calculator.popOperator();
              };
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
              }else if(calculator.isOperatorEmpty() == false && calculator.peekOperator() != '(' )
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
          

          while(calculator.isEmpty() > 1){
            calculator.evaluate();
          }

          double answer = calculator.peekNumber(); 
          std::cout << answer << "\n";
          equationcounter++;                                               // equation count increases 
          memorybuffer.pushequation(equationbuffer,answer);
          drawNewMargin();                                              //drawnewmargin
          
          std::cout << "evaluated the answer" << "\n";
          
          
          
          
          
          */