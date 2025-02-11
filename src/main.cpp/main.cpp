#include "DisplayInit.h"  // Ensure the correct path
#include "ArithmeticStack.h"
#include "Exiomatrix.h"
#include <iostream>
#include "CursorFunctions.h"
#include <vector>


int *currentpageptr = &currentpage;
bool calcenginerun = false;

bool calcresult = false;
bool *calcresultptr = &calcresult; 



std::vector<char>equationbuffer;  // Stores the equation input
int equationLength = 0;  // Tracks how many characters have been entered

void setup() {
    TCA9554PWR_Init(0x00); 
    setCpuFrequencyMhz(80);
    setupDisplay();  // Initialize displays and setup the initial screen
}

void drawCursor() { //blinks the cursor
    if (cursorVisible) {
        tft.fillRect(cursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_BLACK);
    } else {
        tft.fillRect(cursorPos, 5, CURSOR_WIDTH, CURSOR_HEIGHT, ST7735_WHITE);
    }
}

void updateScreen() {
    tft.fillRect(0, 0, 160, 14, ST7735_WHITE);  // Clear equation display area
    
    xPos = 3;  // Reset xPos before drawing characters to the start of the screen 

    for (int i = screenstart; i < equationLength && i < screenstart + MAX_CHARS; i++) { //prints equation from start of the screen to the end of the screen
        tft.setCursor(xPos, 5);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print(equationbuffer[0]);
        xPos += 7; //increase the position then printing a number at the next position
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
            
            // Blink cursor every CURSOR_BLINK_DELAY ms

            if (currentMillis - lastBlinkTime >= CURSOR_BLINK_DELAY) {
                cursorVisible = !cursorVisible;
                drawCursor();
                lastBlinkTime = currentMillis;
            }
            
            int potValue = analogRead(potPin);

            if (potValue < minPotValue) {
                mappedValue = 0;
            } else {
                mappedValue = map(potValue, 500, 4095, 0, 360);
            }

            int degreeChange = mappedValue - previousmapped;
            previousmapped = mappedValue;
            std::cout<<"This is the degreeChange: "<< std::endl;
            

            // Move cursor only within the valid range
            if (degreeChange > 1 && cursorIndex < equationLength && (cursorPos + 7) < 153) {  //checks if the potentiometer changes in the positive direction and the cursor's index is less than equation length an cursor positoin is not at the screen edge
                cursorMoveForward();
                drawCursor();// draws the cursor
                updateScreen(); // updates the screen and writes the equation inside the buffer
            } else if (degreeChange < -3  && cursorIndex > 0) {
                cursorMoveback();
                drawCursor(); //draw new cursor position
                updateScreen(); //print the equation on the screen
            }

            if(key == 'B' && cursorIndex > 0){
                cursorMoveback(); //backspace needs to 
                equationLength--;//reduce the equation length
                //reduce the cursor index and decrement the cursorpos all done in the called function   
                drawCursor(); //draw new cursor position
                updateScreen(); //print the equation on the screen
            }
            if(key == 'C'){
                equationLength = 0; //resets the length of the equation
                cursorPos = 3;
                xPos = 3;
                cursorIndex = 0;
                equationbuffer.clear();
                
                drawCursor(); //draw new cursor position
                updateScreen(); //print out the empty screen
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

                //if the cursor position is at the  and the index is less than the equation length 

                if(cursorPos == 150 && cursorIndex < equationLength)
                {
                  cursorIndex++;  //increase the cursor index this allow us to print a key to the buffer once at the edge of the screen
                }

                // Scroll screen if necessary
                if (equationLength > MAX_CHARS) {
                    screenstart++;
                    std::cout <<"This is the screenstart : "<< screenstart <<std::endl;
                }

                updateScreen();
                drawCursor();
            }
        }
    }
}
