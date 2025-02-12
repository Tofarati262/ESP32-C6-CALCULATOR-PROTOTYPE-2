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

    for (int i = screenstart; i < equationbuffer.size() && i < screenstart + MAX_CHARS; i++) { //prints equation from start of the screen to the end of the screen
        tft.setCursor(xPos, 5);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print(equationbuffer[i]);
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
            if (degreeChange > 4 && cursorIndex < equationbuffer.size() && (cursorPos + 7) < 153) {  //checks if the potentiometer changes in the positive direction and the cursor's index is less than equation length an cursor positoin is not at the screen edge
                cursorMoveForward();
                drawCursor();// draws the cursor
                updateScreen(); // updates the screen and writes the equation inside the buffer
            } else if (degreeChange < -3  && cursorIndex > 0) {
                cursorMoveback();
                drawCursor(); //draw new cursor position
                updateScreen(); //print the equation on the screen
            }

            if(key == 'B' && cursorIndex > 0){ // deletes the characters and updates the screen
                equationbuffer.erase(equationbuffer.begin()+cursorIndex); // the number at the cursor index 
                cursorMoveback(); //backspace needs to 
                //reduce the cursor index and decrement the cursorpos all done in the called function
                drawCursor(); //draw new cursor position
                updateScreen(); //print the equation on the screen
            }
            if(key == 'E'){ // erase the characters inside the vector 
                cursorPos = 3;
                xPos = 3;
                cursorIndex = 0;
                equationbuffer.clear();
                drawCursor(); //draw new cursor position
                updateScreen(); //print out the empty screen
            }

            if(key == 'L'){ //ln(
                lastcursorPos = cursorPos;
                tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
                cursorPos+= 21;
                char temp arr = {'l','n','('};
                for(int i =0; i < 2 ; i++){
                    cursorIndex++;
                    equationbuffer[cursorIndex] =arr[i];
                }


                std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
                drawCursor();
                updateScreen();
            }

             if(key == 'l'){ //log(
                lastcursorPos = cursorPos;
                tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
                cursorPos+= 28;
                char temp arr[]= {'l','o','g', '('};
                for(int i =0; i < 3 ; i++){
                    cursorIndex++;
                    equationbuffer[cursorIndex] =arr[i];
                }


                std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
                drawCursor();
                updateScreen();
            }

            if(key == '('){
                bool rightbracket = true
                lastcursorPos = cursorPos;
                 tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
                cursorPos+= 7;
                cursorIndex++;

                if(rightbracket)
                {
                    equationbuffer[cursorIndex] ='(';
                }else{
                    equationbuffer[cursorIndex] =')';
                }


                std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
                rightbracket = !rightbracket;
                
                drawCursor();
                updateScreen();

            }

            if(key == 'O'){
                esp_sleep_enable_timer_wakeup(10* 100000000); // No timer, stays asleep indefinitely
                esp_deep_sleep_start(); //sets the chip into a deepslep state
            }
            

            if (key != 'z'&& key !='B' && key != 'C' && key != 'a' && key != '=') {
              std::cout <<"This is the pos: "<<cursorPos <<std::endl;
              std::cout <<"This is the equationlength: " <<equationLength <<std::endl;
              std::cout <<"This is the index: "<<cursorIndex <<std::endl;
                // Replace character at current cursor position
                if(cursorIndex >=equationbuffer.size()){
                    equationbuffer.push_back(key);
                }else{
                    equationbuffer[cursorIndex] = key;
                }

                // Increase equation length only if adding at the end

                // Move cursor forward (prevent going off-screen)
                if ((cursorPos + 7) < 155 && cursorIndex < equationbuffer.size()) {
                    cursorPos += 7;
                    cursorIndex++;
                }

                //if the cursor position is at the  and the index is less than the equation length 

                if(cursorPos == 150 && cursorIndex < equationbuffer.size())
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
