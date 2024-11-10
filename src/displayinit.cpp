#include <diplayinit.h>

// DisplayInit.cpp


// Pin definitions
const int buttonPin = 3;
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
    while (true) {
        int buttonState = digitalRead(buttonPin);
        
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

            if (buttonState == LOW) {  // Button pressed
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

            if (buttonState == LOW) {  // Button pressed
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
    // Only draw a new line when the button is pressed
    if (digitalRead(buttonPin) == LOW) {
      // Clear the previous line
      tft.drawRect(0, screenline, 160, 1, ST7735_BLACK);

      // Update `screenline` by moving it down
      screenline += 10;

      // Draw the new line
      tft.drawRect(0, screenline, 160, 1, ST7735_BLACK);
      Serial.println("Button pressed");

      // Add a delay to debounce the button press
      delay(200);  // Adjust delay as needed
    }

    // Optional: Reset `screenline` if it goes beyond the display height
    if (screenline > 128) {  // Replace 128 with your screen height if different
      screenline = 0;
    }
  }
}


void (*pages[])() = {Startup,drawmenu,calcengine};