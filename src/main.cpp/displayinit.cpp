#include "esp32-hal-gpio.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "ArithmeticStack.h"
// DisplayInit.cpp

//calculator logic
u_int8_t xincrement=1;
bool calcresult = false;
bool *calcresultptr = &calcresult; 

uint16_t mappedValue = 0;
uint16_t lastMappedValue = 0;
uint8_t currentpage = 0;
uint8_t screencount = 0;

// Potentiometer state variables
uint16_t *mappedValueptr = &mappedValue;


uint16_t *lastMappedValueptr =&lastMappedValue ;

// screen count 
uint8_t *screencountptr = &screencount;

//State Tracking 




// Display objects
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// to clear displays inbetween page changes
void cleanscreen(){
    tft.fillScreen(ST7735_WHITE);
}
// Initialize displays and setup
void setupDisplay() {
    Serial.begin(9600);
    tft.initR(INITR_BLACKTAB);
    tft.setFont(&FreeSerifBold9pt7b);
    tft.setRotation(3);
    tft.fillScreen(ST7735_WHITE);
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
    tft.setTextSize(1);
    pinMode(buttonPin, INPUT_PULLUP);
}

// Implement the rest of your functions here
void Startup() {
    pinMode(buttonPin,OUTPUT);
    digitalWrite(1,LOW);
     TCA9554PWR_Init(0x00);
    Mode_EXIO(buttonPin, 1);

    while (Read_EXIO(buttonPin) == 1) {
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
        tft.fillRect(60, 100, 60, 10, ST7735_WHITE);
    }
    digitalWrite(1,HIGH);
    tft.fillScreen(ST7735_WHITE);
    Serial.println("Startup complete, exiting loop.");
    currentpage++;
}

// Continue with the rest of the functions here...




void drawmenu() {
  digitalWrite(1,LOW);
    // Continuously loop until the user performs an action
    while (true) {
        
        
        // Read potentiometer to update mappedValue
        int potValue = analogRead(potPin);  // Read potentiometer
        if (potValue < minPotValue) {
            *mappedValueptr = 0;
        } else {
           *mappedValueptr = map(potValue, minPotValue, maxPotValue, 10, 360);
        }

        // Draw the menu elements
        tft.drawRect(38, 100, 130, 15, ST7735_WHITE);
        if (*mappedValueptr <= 180) {  // Return button highlighted
           tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);  
            tft.setCursor(90, 100);
            tft.print("Return");

            if (Read_EXIO(buttonPin) ==  0) {  // Button pressed
                digitalWrite(1,HIGH);
                cleanscreen();
               currentpage++;  // Increment page
                break;  // Exit the loop and update the page
            }
        } else if (*mappedValueptr > 180) {  // Enter button highlighted
           tft.setTextColor(ST7735_BLACK, ST7735_WHITE); 
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(90, 100);
            tft.print("Return");

             if (Read_EXIO(buttonPin) == 0) {  // Button pressed
                cleanscreen();
                digitalWrite(1,HIGH);
                currentpage--;  // Decrement page
                break;  // Exit the loop and update the page
            }
        }
    }
}

  void calcengine() {
    double numbuffer =0.0;
    double decimalplace = 0.1;
    bool decimalfound = false;
    bool lastpushednum = true;
    char equationbuffer[MAXBUFFER];
    tft.drawRect(0, 15, 160, 1, ST7735_BLACK);
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
        }
        if ( key == '='){
          while(calc.isEmpty() == 1){
            result += calc.evaluate();
          }
          Serial.print(result);

        }
    }
  }
}  




void (*pages[])() = {Startup,drawmenu,calcengine};