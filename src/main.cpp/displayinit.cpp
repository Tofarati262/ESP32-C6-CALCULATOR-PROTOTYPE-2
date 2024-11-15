#include "DisplayInit.h"
// DisplayInit.cpp


// Pin definitions

const int potPin = 4;

// Button state variables
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 100;

// Potentiometer state variables
int value = 0;
int mappedValue = 0;
int lastMappedValue = -1;
const int minPotValue = 500;
const int maxPotValue = 4095;
int screenline = 20;
int currentpage = 0;
bool buttonpressed = false;
const byte rows = 1;
const byte columns = 5;

// Display objects
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//keypad for calculator 


char hexaKeys[rows][columns] = {
 
  {'C', 'O', 'M', 'R', '='},      // Row 1: Clear and hold to clear entry, math button: {degrees, absolute value,modulus}, Mode, Recall, Equals
 /*({'B', 'L', '(', ')', 'T'},      // Row 2: Backspace, Logarithm, Open Parenthesis, Close Parenthesis, Trigonometric
  {'F', 'P', '7', '8', '9'},      // Row 3: Factorial, Pi, 7, 8, 9
  {'X', '/', 'S', '4', '5'},      // Row 4: Multiplication, Division, Square root, 4, 5
  {'6', '+', '-', '^', '1'},      // Row 5: 6, Addition, Subtraction, Exponentiation, 1
  {'2', '3', 'A', '0', '.'},      // Row 6: 2, 3, Trig Functions, 0, Decimal
  {'G', 'N', 'D', 'Q', 'R'},      // Row 7: Log base-10, Natural Log, Degrees toggle, Constant (Euler's number), square root)*/ 
};



byte rowPins[rows] = {TCA9554_EXIO2};
byte colPins[columns] = {9,18,19, 7,20};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, rows, columns);

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
   
}

// Implement the rest of your functions here
void Startup() {
    while (Read_EXIO(TCA9554_EXIO6)== 1) {
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
    currentpage++;
}

// Continue with the rest of the functions here...
void knob() {
    int potValue = analogRead(potPin);  // Read the potentiometer value (0-4095)
  if (potValue < minPotValue) {
    mappedValue = 0;
  } else {
    mappedValue = map(potValue, minPotValue, maxPotValue, 10, 360);
  }
  if (mappedValue != lastMappedValue) {
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" -> Mapped Value: ");
    Serial.println(mappedValue);
    lastMappedValue = mappedValue;
  }
}


void drawmenu() {
    // Continuously loop until the user performs an action
    while (true) {
        uint8_t buttonState = Read_EXIO(TCA9554_EXIO6);
        
        // Read potentiometer to update mappedValue
        int potValue = analogRead(potPin);  // Read potentiometer
        if (potValue < minPotValue) {
            mappedValue = 0;
        } else {
            mappedValue = map(potValue, minPotValue, maxPotValue, 10, 360);
        }

        // Draw the menu elements
        tft.drawRect(38, 100, 130, 15, ST7735_WHITE);
        if (mappedValue > 180) {  // Return button highlighted
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE); 
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(90, 100);
            tft.print("Return");

            if (buttonState == 0) {  // Button pressed
                cleanscreen();
                currentpage--;  // Decrement page
                break;  // Exit the loop and update the page
            }
        } else if (mappedValue <= 180) {  // Enter button highlighted
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
            tft.setCursor(40, 100);
            tft.print("Enter");
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);  
            tft.setCursor(90, 100);
            tft.print("Return");

            if (buttonState == 0) {  // Button pressed
                currentpage++;  // Increment page
                cleanscreen();
                break;  // Exit the loop and update the page
            }
        }

        delay(100);  // Small delay to prevent button bouncing or excessive potentiometer reads
    }
}

void calcengine() {
    while (true) {
        char key = keypad.getKey();  // Use the keypad instance here
        if (key) {  // Only print if a key is pressed
            Serial.println(key);
        }
    }
}


void (*pages[])() = {Startup,drawmenu,calcengine};