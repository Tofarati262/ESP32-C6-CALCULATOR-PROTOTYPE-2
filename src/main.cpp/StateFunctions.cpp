#include "StateFunctions.h"
#include "StateMachine.h"
#include "Init.h"
#include "string.h"
#include "Exiomatrix.h"
#include "Arithmetic.h"
#include "InputBuffer.h"

Adafruit_ST7735  tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void Start_State()
{
    pinMode(5, INPUT); 
    while (digitalRead(1) == LOW) {
        tft.drawRect(25, 40, 120, 35, ST7735_WHITE);
        tft.setFont(&FreeSerifBold9pt7b);
        tft.setTextSize(2);
        tft.setTextColor(tft.color565(200, 0, 0), ST7735_WHITE);
        tft.setCursor(25, 70);
        tft.print("Finmor");
        tft.drawRect(60, 100, 60, 10, ST7735_WHITE);
        tft.setFont();
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft.setCursor(60, 100);
        tft.print("Continue");
        delay(900);
        tft.fillRect(60, 100, 60, 10, ST7735_WHITE);
    }
    tft.fillScreen(ST7735_WHITE);
    Serial.println("Startup complete, exiting loop.");
    current_states = states::menu_state;

}

void Menu_State()
{
    while (true) {
        
        
        // Read potentiometer to update mappedValue
        int potValue = analogRead(potPin);  // Read potentiometer
        if (potValue < minPotValue) {
            mappedValue = 0;
        } else {
            mappedValue = map(potValue, minPotValue, maxPotValue, 10, 360);
        }

        // Draw the menu elements
        tft.drawRect(38, 100, 130, 15, ST7735_WHITE);
        if (mappedValue <= 180) {  // Return button highlighted
           tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);  
            tft.setCursor(90, 100);
            tft.print("Return");

            if (digitalRead(buttonPin) ==  1) {  // Button pressed
                current_states = states::calculator_state;  // Increment page
                cleanscreen();
                break;  // Exit the loop and update the page
            }
        } else if (mappedValue > 180) {  // Enter button highlighted
           tft.setTextColor(ST7735_BLACK, ST7735_WHITE); 
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(90, 100);
            tft.print("Return");

             if (digitalRead(buttonPin) == 1) {  // Button pressed
                cleanscreen();
                current_states = states::start_state;;  // Decrement page
                break;  // Exit the loop and update the page
            }
        }
    }
}

void Calculator_State()
{   std::string String = "";
    double numbuffer =0.0;
    double decimalplace = 0.1;
    bool decimalfound = false;
    bool numbufferInUse = false; // Indicates if a number is being entered
    tft.drawRect(0, 15, 160, 1, ST7735_WHITE);
    tft.drawRect(0, 30, 160, 1, ST7735_WHITE);
    delay(100);
    CALCSTACK calc;
    InputBuffer inputbuffer;

  
    while (true) {
      char key = ButtonLoop();
      String += key;
      if (key!= 'z' && calcresult == false){
      delay(500);
        if (screencount <= 22 ){
          tft.setCursor(xincrement,5);
          tft.setTextSize(1);
          tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
          if(key!= '='&& key!='O'&& key!='B'){
            tft.print(key);
            xincrement+=7;
            screencount++;
            Serial.println(screencount);
          }
        }
      }else if (key == '=') {
        if(calc.sizeofnumberstack() == calc.sizeofoperatorstack()){
          Serial.println("Error: ");
        }else{
          calc.evaluate(); // Evaluate the current expression
          double  result = calc.peekNumber(); // Get the result
          int accuracy = calc.countDecimalPlaces(result);
          inputbuffer.PushInput(String,result,accuracy);
          DrawLogicState(); //this displays the list of equations

        }
      } else if (key == 'O') {
        // Clear the screen and reset the stack
        calc = CALCSTACK(); // Reinitialize the stack
        calcresult= false;
        xincrement = 0;
        screencount = 0;
        tft.fillScreen(ST7735_WHITE); // Clear the TFT display
        tft.setCursor(0, 15);
      }else if (key == 'B') { // Handle backspace
        if (  screencount > 0){
          screencount--; // Decrement screen count
          Serial.println(screencount);
          tft.setCursor(xincrement-7, 5);
          tft.setTextSize(1);
          tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
          tft.print(" "); // Clear the character on display
          xincrement -= 7; // Move cursor back
        }
      }else if(isdigit(key)){
        numbufferInUse = true;
        if(decimalfound){
          numbuffer += (key - '0') * decimalplace;
          decimalplace *= 0.1; // this enables the next number to have a higher decimal place ex: 2.22  2+ 0.2 +0.02
        }else{
          numbuffer = numbuffer * 10 + (key - '0') ; //  10 * 10 + 2 = 102
        }
      }else if (calc.isOperator(key)){
        if(numbufferInUse){
            calc.pushNumber(numbuffer);
            numbufferInUse = false;
            numbuffer = 0.0;
            decimalplace = 0.1;
        }
        calc.pushOperator(key);
      }else if (key == '.'){
        if (!decimalfound) {
          decimalfound = true; // Start adding decimal digits
        } else {
          // Handle invalid multiple decimals
          Serial.println("Error: Multiple decimal points");
        }
      }else if(key=='esc'){
        DrawLogicState();
        break;
      }
  }   
}



void DrawLogicState() {
  // Clear display section for updated results
  tft.fillRect(0, counter * 30, 160, 1, ST7735_BLACK);
  tft.setCursor(145, counter * 30 - 10);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  tft.setTextSize(1);

  // Display result
  if (counter < 3) {  // Limit to 3 results on the screen
      tft.print(InputBuffer::RetrieveInput, accuracy);  // Display result with specified precision
      counter++;
  } else {
      tft.fillScreen(ST7735_WHITE);  // Clear screen if too many entries
      counter = 0;
  }
}
