#include <string.h>
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "ArithmeticStack.h"
#include "iostream"

// DisplayInit.cpp



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

MenuItem menu[3] = {
    {"WIFI", 7, 29},
    {"Calculator", 7, 59},
    {"Tik-Tac-Toe", 7, 89},
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
    int LastSelected;

    tft.setCursor(50,1);
    tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
    tft.print("Applications");

    tft.drawRect(5, menu[0].y - 5, 150, 15, ST7735_BLACK);
    tft.drawRect(5, menu[1].y - 5, 150, 15, ST7735_BLACK);
    tft.drawRect(5, menu[2].y - 5, 150, 15, ST7735_BLACK);

    while (true) { 
      
      // Read potentiometer to update mappedValue



      if(Read_EXIO(buttonPin) == 0){
        if(selected == 1){ // when calculator is selected 
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

      
      mappedValue = potentiometer1.getPotValue();

      timer1 = millis();

      tft.setCursor(130,  menu[selected].y);
      tft.print("<--");

      tft.setCursor(130,  menu[LastSelected].y);
      tft.print("    ");

      tft.setTextSize(1); // Make selected text bigger
      tft.setCursor(menu[0].x, menu[0].y); 
      tft.print(menu[0].name);
      tft.setCursor(menu[1].x, menu[1].y); 
      tft.print(menu[1].name);
      tft.setCursor(menu[2].x, menu[2].y); 
      tft.print(menu[2].name);
      
    // Handle menu navigation
    if (mappedValue > lastMappedValue +5  && (timer1-timer2 > 10)) {
      LastSelected = selected;
      selected++;
      if (selected > 2) {
          selected = 0;
      } 
    }

    if (mappedValue < lastMappedValue-5 && (timer1-timer2 > 10)) {
      LastSelected = selected;
      selected--;
      if (selected <0){
        selected = 2;
      }
    }

    lastMappedValue = mappedValue;
    timer2 = timer1;
  }
}

  




void (*pages[])() = {Startup,drawmenu};