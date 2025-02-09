#include "DisplayInit.h"  // Ensure the correct path
#include "ArithmeticStack.h"
#include "Exiomatrix.h"
#include <iostream>

#define CURSOR_WIDTH 5
#define CURSOR_HEIGHT 7
#define CURSOR_BLINK_DELAY 100  // Blinking speed in milliseconds
#define MAX_CHARS 22  // Maximum characters visible before scrolling

uint8_t *currentpageptr = &currentpage;
bool calcenginerun = false;

bool calcresult = false;
bool *calcresultptr = &calcresult; 

uint8_t previousmapped = 0;

uint8_t *screenendptr = &screencount;
uint8_t screenstart = 0;

int cursorIndex= 0;
int cursorPos = 3;  // Cursor X position
int xPos= 3;
int lastcursorPos = 0;
bool cursorVisible = true;  // Blinking state
unsigned long lastBlinkTime = 0;

char equationbuffer[MAXBUFFER];  // Stores the equation input
int equationLength = 0;  // Tracks how many characters have been entered

void setup() {
    TCA9554PWR_Init(0x00); 
    setCpuFrequencyMhz(80);
    setupDisplay();  // Initialize displays and setup the initial screen
}

void drawCursor() {
    if (cursorVisible) {
        tft.fillRect(cursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_BLACK);
    } else {
        tft.fillRect(cursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
    }
}

void updateScreen() {
    tft.fillRect(0, 0, 160, 14, ST7735_WHITE);  // Clear equation display area
    
    xPos = 3;  // Reset xPos before drawing characters

    for (int i = screenstart; i < equationLength && i < screenstart + MAX_CHARS; i++) {
        tft.setCursor(xPos, 5);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print(equationbuffer[i]);
        xPos += 7;
    }


    drawCursor();
}

void loop() {
    if (*currentpageptr < 2) {
        (*pages[*currentpageptr])();
    }

    if (*currentpageptr == 2) {
        tft.drawRect(0, 0, 160, 14, ST7735_WHITE);  // Input box
        tft.drawRect(0, 30, 160, 1, ST7735_WHITE);  // Margin

        while (true) {
            
            char key = loopy();  // Get key input
            unsigned long currentMillis = millis();
            
            int potValue = analogRead(potPin);

            if (potValue < minPotValue) {
                mappedValue = 0;
            } else {
                mappedValue = map(potValue, 500, 4095, 0, 360);
            }

            int degreeChange = mappedValue - previousmapped;
            previousmapped = mappedValue;

            // Move cursor only within the valid range
            if (degreeChange > 1 && cursorIndex < equationLength && (cursorPos + 7) < 153) { 
                lastcursorPos = cursorPos;
                tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
                cursorPos += 7;
                cursorIndex++;
                std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
                drawCursor();
                updateScreen();
            } else if (key == 'B' && cursorIndex > 0) {
                lastcursorPos = cursorPos;
                cursorPos -= 7;
                tft.fillRect(lastcursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
                cursorIndex--;
                 std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
                if(cursorIndex < screenstart)
                {
                  std::cout <<"This is the screenstart : "<<screenstart <<std::endl;
                  screenstart--;
                }
                drawCursor();
                updateScreen();
            }

            // Blink cursor every CURSOR_BLINK_DELAY ms
            if (currentMillis - lastBlinkTime >= CURSOR_BLINK_DELAY) {
                cursorVisible = !cursorVisible;
                drawCursor();
                lastBlinkTime = currentMillis;
            }

            if (key != 'z'&& key !='B') {
              std::cout <<"This is the pos: "<<cursorPos <<std::endl;
              std::cout <<"This is the equationlength: " <<equationLength <<std::endl;
              std::cout <<"This is the index: "<<cursorIndex <<std::endl;
                // Replace character at current cursor position
                equationbuffer[cursorIndex] = key;

                // Increase equation length only if adding at the end
                if (cursorIndex == equationLength) {
                    equationLength++;  
                }

                // Move cursor forward (prevent going off-screen)
                if ((cursorPos + 7) < 155 && cursorIndex < equationLength) {
                    cursorPos += 7;
                    cursorIndex++;
                }

                if(cursorPos == 150 && cursorIndex < equationLength)
                {
                  cursorIndex++;
                }

                // Scroll screen if necessary
                if (equationLength > MAX_CHARS) {
                    screenstart++;
                    std::cout <<"This is the screenstart : "<<screenstart <<std::endl;
                }

                updateScreen();
                drawCursor();
            }
        }
    }
}
