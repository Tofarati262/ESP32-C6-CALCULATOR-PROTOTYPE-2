#include <string.h>
#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "ArithmeticStack.h"
#include "iostream"

// DisplayInit.cpp
class Potentiometer
{
private:
  
public:
  int getPotValue()
  {
    int potValue = analogRead(potPin);  // Read potentiometer
      if (potValue < minPotValue) {
        mappedValue = 0;
      } else {
        mappedValue = map(potValue, minPotValue, maxPotValue, 10, 360);
    }

    return mappedValue;

  }

};



int mappedValue = 0;
int lastMappedValue = 0;
int screencount = 0;

  int selected = -1;
    int timer1 = 0;
    int timer2 = 0;

// Potentiometer state variables
int *mappedValueptr = &mappedValue;
int *lastMappedValueptr =&lastMappedValue ;

// Display objects
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

MenuItem menu[4] = {
    {"WIFI", 60, 9},
    {"Weather", 56, 39},
    {"Tik-Tak-Toe", 47, 69},
    {"Calculator", 51, 99}
};


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
  pinMode(buttonPin,OUTPUT);
    digitalWrite(1,LOW);
     TCA9554PWR_Init(0x00);
    Mode_EXIO(buttonPin, 1);
    // Continuously loop until the user performs an action
    Potentiometer potentiometer1;

    while (true) { 
      Serial.print(selected);       
        // Read potentiometer to update mappedValue
      mappedValue = potentiometer1.getPotValue();

      timer1 = millis();

        if(Read_EXIO(buttonPin) == 0){
          if(selected == 3){ // when calculator is selected 
            currentpage = 6;
            break;
          }else if(selected ==0 ){ // when wifi is selected
            currentpage = 3;
            break;
          }else if(selected == 2){
            currentpage = 5;
            break;
          }
        }

        for (int i = 0; i < 4; i++) {
          if (selected == i) {  // Highlight selected item in bold
             tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
              tft.setTextSize(1); // Make selected text bigger
              tft.setCursor(menu[i].x, menu[i].y); 
              tft.print(menu[i].name);
          }
          if(selected != i){  // Normal text for unselected items
              tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
              tft.setTextSize(1);
              tft.setCursor(menu[i].x, menu[i].y);
              tft.print(menu[i].name);
          }
        }
        
      // Handle menu navigation
        if (mappedValue > lastMappedValue+4 && (timer1-timer2 > 50)) {
          selected++;
          if (selected > 3) {
              selected = 0;
          } 
        }
        if (mappedValue < lastMappedValue-4 && (timer1-timer2 > 50)) {
          selected--;
          if (selected <1){
            selected = 3;
          }
        }
        lastMappedValue = mappedValue;
        timer2 = timer1;
  }
}

  




void (*pages[])() = {Startup,drawmenu};