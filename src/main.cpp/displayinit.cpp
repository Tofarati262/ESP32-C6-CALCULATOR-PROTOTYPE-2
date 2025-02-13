#include "esp32-hal-gpio.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "ArithmeticStack.h"
// DisplayInit.cpp



int mappedValue = 0;
int lastMappedValue = 0;
int screencount = 0;

// Potentiometer state variables
int *mappedValueptr = &mappedValue;
int *lastMappedValueptr =&lastMappedValue ;

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

  




void (*pages[])() = {Startup,drawmenu};