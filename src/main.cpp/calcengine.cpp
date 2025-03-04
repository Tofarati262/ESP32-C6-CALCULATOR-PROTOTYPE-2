#include "CursorFunctions.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"
#include "iostream"
#include <vector>

bool calcenginerun = false;

bool calcresult = false;
bool *calcresultptr = &calcresult; 

bool rightbracket = true;


std::vector<char>equationbuffer;  // Stores the equation input
int equationLength = 0;  // Tracks how many characters have been entered




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


void calcrun(){
    tft.fillScreen(ST7735_WHITE);
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
            mappedValue = map(potValue, 500, 4095, 0, 500);
        }

        int speedchange = mappedValue - previousmapped;
        previousmapped = mappedValue;
        std::cout<<"This is the degreeChange: "<< speedchange <<std::endl;

        // Move cursor only within the valid range
        if (speedchange > 5 && cursorIndex < equationbuffer.size() && (cursorPos + 7) < 153) {  //checks if the potentiometer changes in the positive direction and the cursor's index is less than equation length an cursor positoin is not at the screen edge
            cursorMoveForward();
            drawCursor();// draws the cursor
            updateScreen(); // updates the screen and writes the equation inside the buffer
        } else if (speedchange < -5  && cursorIndex > 0) {
            cursorMoveback();
            drawCursor(); //draw new cursor position
            updateScreen(); //print the equation on the screen
        }

        if(key == 'B' && !equationbuffer.empty() && cursorIndex < equationbuffer.size())
        { // deletes the characters and updates the screen
            cursorDelete(); //backspace needs to 
            //reduce the cursor index and decrement the cursorpos all done in the called function
            drawCursor(); //draw new cursor position
            updateScreen(); //print the equation on the screen
        }
        if(key == 'E'){ // erase the characters inside the vector 
          equationbuffer.clear();
            xPos = 3;
            cursorIndex = 0;
             cursorPos = 3;
            drawCursor(); //draw new cursor position
            updateScreen(); //print out the empty screen
        }
        
        if(key == 'L'){ //ln(
            char temp[] = {'l','n','('};
            if(equationbuffer.size()==0){ // if its at zero
                equationbuffer.push_back(temp[0]);
                cursorIndex++;
                equationbuffer.push_back(temp[1]);
                cursorIndex++;
                equationbuffer.push_back(temp[2]);
                cursorIndex++;
            }else{ //if the eqautionbuffersize is not at zero
              for(int i =0; i < 3 ; i++){
                  equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
                  cursorIndex++;
              }
            }
          

            lastcursorPos = cursorPos;
            tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
            std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
            cursorPos+= 21;
            drawCursor();
            updateScreen();
        }

         if(key == 'l'){ //log(
            lastcursorPos = cursorPos;
            tft.fillRect(lastcursorPos,5,CURSOR_WIDTH,CURSOR_HEIGHT,ST7735_WHITE);
            cursorPos+= 28;
            char temp[]= {'l','o','g', '('};
           if(equationbuffer.size()==0){ // if its at zero
                equationbuffer.push_back(temp[0]);
                cursorIndex++;
                equationbuffer.push_back(temp[1]);
                cursorIndex++;
                equationbuffer.push_back(temp[2]);
                cursorIndex++;
                equationbuffer.push_back(temp[3]);
                cursorIndex++;
            }else{ //if the eqautionbuffersize is not at zero
              for(int i =0; i < 4 ; i++){
                equationbuffer.insert(equationbuffer.begin() + cursorIndex,temp[i]);
                cursorIndex++;
              }
            }


            std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
            drawCursor();
            updateScreen();
        }
        

        if(key == '('){

            if(rightbracket)
            {
               key = '(';
            }else{
              key = ')';
            }
            std::cout <<"This is the cursor index: "<<cursorIndex <<std::endl;
            rightbracket = !rightbracket;
        }

        if(key == 'O'){
            esp_sleep_enable_timer_wakeup(10* 1000000); // No timer, stays asleep indefinitely
            esp_deep_sleep_start(); //sets the chip into a deepslep state
            
        }
        
        if(key == 'F'){
          
        }

        if (key != 'z'&& key !='B' && key != 'E' && key != 'a' && key != '=' && key != 'l'&& key!='L'&& key != 'T'&& key != 'F') {
            // Replace character at current cursor position
            if(cursorIndex >=equationbuffer.size()){
                equationbuffer.push_back(key);
            }else{
                equationbuffer.at(cursorIndex) = key;
            }

            if ((cursorPos + 7) < 155 && cursorIndex < equationbuffer.size()) {
                cursorPos += 7;
                cursorIndex++;
            }
            if(cursorPos == 150 && cursorIndex < equationbuffer.size())
              {
                cursorIndex++;  //increase the cursor index this allow us to print a key to the buffer once at the edge of the screen
              }

              // Scroll screen if necessary
            if (equationLength > MAX_CHARS) {
                screenstart++;
                std::cout <<"This is the screenstart : "<< screenstart <<std::endl;
            }

            std::cout <<"This is the pos: "<<cursorPos <<std::endl;
            std::cout <<"This is the equationlength: " <<equationLength <<std::endl;
            std::cout <<"This is the index: "<<cursorIndex <<std::endl;

            // Increase equation length only if adding at the end

            // Move cursor forward (prevent going off-screen)


            //if the cursor position is at the  and the index is less than the equation length 



            updateScreen();
            drawCursor();
        }
    }
}