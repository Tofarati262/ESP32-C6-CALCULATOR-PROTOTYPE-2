#include "DisplayInit.h"  // Ensure the correct path
#include "ArithmeticStack.h"
#include "Exiomatrix.h"

uint8_t *currentpageptr = &currentpage;
bool calcenginerun = false;

u_int8_t xincrement=1;
bool calcresult = false;
bool *calcresultptr = &calcresult; 

uint8_t *screencountptr = &screencount;



void setup() {
  TCA9554PWR_Init(0x00); 
    setCpuFrequencyMhz(80);
  setupDisplay();  // Initialize displays and setup the initial screen
}

void loop() {
    // Call the current page function

    if(*currentpageptr <2){
      (*pages[*currentpageptr])();
    }

    // Increment the page index
    if (*currentpageptr == 2) {
    double numbuffer =0.0;
    double decimalplace = 0.1;
    bool decimalfound = false;
    bool lastpushednum = true;
    char equationbuffer[MAXBUFFER];
    tft.drawRect(0, 0, 160, 14, ST7735_WHITE);
    tft.drawRect(0, 30, 160, 1, ST7735_WHITE);
    CALCSTACK calc;
    int result = 0;

    while (true) {
      delay(100);
      char key = loopy();          
      if(key!= 'z' && *calcresultptr == false){
          if (*screencountptr <= 21 ){
            tft.setCursor(xincrement,5);
            tft.setTextSize(1);
            tft.setTextColor(ST7735_BLACK,ST7735_WHITE);

            if(key == '1' || key== '2' || key == '3'||key == '4'||key == '5'||key == '6'||key == '7'||key == '8'||key == '9'||key == '0'){
              double parser = key - '0'; // converts char to double 
              calc.pushNumber(parser); // pushes it to stack
              lastpushednum = true; // last pushed number is tracked as a double 
            }

            if(calc.isOperator(key)){ //check is the char is an operator
              calc.pushOperator(key);
              lastpushednum = false;// to track the last pushed number as an operator
            }


            if(key!= '='&& key!='O'&& key!='B'){
              tft.print(key);
              xincrement+=7;
              (*screencountptr)++;
              Serial.println(*screencountptr);
            }
          }
      }
          if (key == 'B') { // Handle backspace
            if (  *screencountptr > 0){
              (*screencountptr)--; // Decrement screen count
              Serial.println(*screencountptr);
              tft.setCursor(xincrement-7, 5);
              tft.setTextSize(1);
              tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
              tft.print(" "); // Clear the character on display
              xincrement -= 7; // Move cursor back
               if(lastpushednum == false) //meaning an operator was pushed
               {
                 calc.popOperator();
               }else{
                  calc.popNumber();
               }
          }
        }
        if (key == 'O') {
          // Clear the screen and reset the stack
          calc = CALCSTACK(); // Reinitialize the stack
          *calcresultptr= false;
          lastpushednum = true;
          xincrement = 0;
          *screencountptr = 0;
          tft.fillRect(0, 0, 160, 14, ST7735_WHITE);
          result = 0;
        }
        if ( key == '='){
          result = calc.evaluate();
          *calcresultptr=true;
          
          Serial.print(result);
          tft.drawRect(0, 40, 160, 1, ST7735_BLACK);
          tft.setCursor( 145-sizeof(result), 30);
          tft.print(result);
          tft.setTextSize(1);
        }
      
    }
  }
}
