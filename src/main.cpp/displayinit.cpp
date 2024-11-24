#include "esp32-hal-gpio.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "ArithmeticStack.h"
// DisplayInit.cpp

//calculator logic
u_int8_t xincrement=1; 
// Pin definitions
const int buttonPin = 18;
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
    while (digitalRead(buttonPin) == HIGH) {
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

void button() {
   int reading = digitalRead(buttonPin);
  if (reading == LOW && lastButtonState == HIGH && (millis() - lastPressTime) > debounceDelay) {
    Serial.println("Button Pressed");
    lastPressTime = millis();
    value = (value + 1) % 2;
    buttonpressed = true;
  } else {
    buttonpressed = false;
  }
  lastButtonState = reading;
}

void drawmenu() {
    // Continuously loop until the user performs an action
    while (digitalRead(buttonPin) == HIGH) {
        
        
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

            if (digitalRead(buttonPin) ==  0) {  // Button pressed
                currentpage++;  // Increment page
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

             if (digitalRead(buttonPin) == 0) {  // Button pressed
                cleanscreen();
                currentpage--;  // Decrement page
                break;  // Exit the loop and update the page
            }
        }
    }
}

void calcengine() {
  int screencount = 0;
  double numbuffer =0.0;
  double decimalplace = 0.1;
  bool decimalfound = false;
  char equationbuffer[MAXBUFFER];
  tft.drawRect(0, 15, 160, 1, ST7735_WHITE);
  tft.drawRect(0, 30, 160, 1, ST7735_WHITE);
  delay(100);
  CALCSTACK calc;

  while (true) {
    char key = loopy();
    if (isdigit(key)) {
      if (decimalfound){
        numbuffer  += (key - '0')*decimalplace;
        decimalplace *= 0.1;
      }else{
        numbuffer = numbuffer* 10 + (key - '0'); // Convert char to int
      }
    } else if (calc.isOperator(key)) {
       if (numbuffer != 0 || key == '-' ) {  // Include negative numbers (e.g., -5)
        calc.pushNumber(numbuffer);
      }
      decimalfound = false;
      decimalplace = 0.1;
      calc.pushOperator(key);
      numbuffer = 0.0; // Reset the buffer for the next number
    }else if (key == '.'){
      decimalfound = true;
    } else if (key == '=') {
                // Perform evaluation when '=' is pressed
      if (numbuffer != 0) {
        calc.pushNumber(numbuffer); // Push the last number in the buffer
        numbuffer = 0; // Reset the buffer
      }

      try {
                    calc.evaluate(); // Evaluate the current expression
                    double  result = calc.peekNumber(); // Get the result
                    int accuracy = calc.countDecimalPlaces(result);
                    
                    // Display the result on the screen
                    tft.drawRect(0, 30, 160, 1, ST7735_BLACK);
                    tft.setCursor(145, 20);
                    tft.print(result,accuracy);

                } catch (const std::exception& e) {
                    tft.setCursor(100, 30);
                    tft.print("Error: ");
                    tft.print(e.what());
                }          
    } else if (key == 'O') {
                // Clear the screen and reset the stack
                calc = CALCSTACK(); // Reinitialize the stack
                xincrement = 0;
                screencount = 0;
                tft.fillScreen(ST7735_WHITE); // Clear the TFT display
                tft.setCursor(0, 15);
    }
    if(key!= 'z'){
      delay(500);
      screencount++;
      if (screencount <= 22 ){
          tft.setCursor(xincrement,5);
          tft.setTextSize(1);
          tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
          if(key!= '='&& key!='O'){
            tft.print(key);
            xincrement+=7;
          }
      }
    }else(key== 'B'){
       delay(500);
      screencount++;
      if (screencount <= 22 ){
          tft.setCursor(xincrement,5);
          tft.setTextSize(1);
          tft.setTextColor(ST7735_WHITE,ST7735_WHITE);
          tft.print(key);
          xincrement-=7;
      }
    }

  }
}


void (*pages[])() = {Startup,drawmenu,calcengine};