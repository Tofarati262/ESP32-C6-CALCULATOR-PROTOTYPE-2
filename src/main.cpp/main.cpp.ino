#include "DisplayInit.h"  // Ensure the correct path
#include "ArithmeticStack.h"
#include "Exiomatrix.h"

uint8_t *currentpageptr = &currentpage;
bool calcenginerun = false;

u_int8_t xincrement=1;
bool calcresult = false;
bool *calcresultptr = &calcresult; 

uint8_t *screencountptr = &screencount;

double buffer = 0.0;
bool bracketright = false;



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
    bool lastnum = true; // track what the last button pressed was number or char
    double numbuffer =0.0;
    double decimalplace = 0.1;
    bool decimalfound = false;
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

           
            


            if(key!= '=' && key!='O' && key!='B' && key!='M' &&  key != 'R' && key!= 'C' && key != 'T' && key != 'F' && key != 'L' && key != '(' && key!= 'G'){
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
          }
        }
        if (key == 'O') {
          // Clear the screen and reset the stack
          calc = CALCSTACK(); // Reinitialize the stack
          buffer = 0;
          *calcresultptr= false;
          xincrement = 0;
          *screencountptr = 0;
          tft.fillRect(0, 0, 160, 14, ST7735_WHITE);
          result = 0;
        }
        if(key == 'L')
        {
          tft.setTextSize(1);
          tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
          tft.setCursor(xincrement, 5);
          tft.print("Log");
          xincrement +=7;
          tft.print('(');
          xincrement +=18;
        }
        if(key == '(')
        {
          tft.setTextSize(1);
          tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
          tft.setCursor(xincrement, 5);
          if (bracketright){
            tft.print(')');
            xincrement +=7;
          }else{
           tft.print('(');
           xincrement +=7;
          }
          bracketright = !bracketright; // Toggle the bracket state

        }
        if(key == 'G'){
          tft.setCursor(xincrement, 5);
          tft.setTextSize(1);
          tft.print("log");

          tft.setCursor(xincrement + 18, 8); // Move "10" lower
          tft.setTextSize(0); // Make it smaller like a subscript
          tft.print("10");

          xincrement += 24; // Adjust cursor for next character

        }
      }
    }
  }
