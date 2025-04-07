#include "tacEngine.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"

void resetGame() {
    tft.fillScreen(ST7735_WHITE); // Clear the screen

    // Redraw the tic-tac-toe grid
    auto color = ST7735_BLACK;
    tft.setCursor(47, 5);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_BLACK);
    tft.print("Tic Tac Toe");

    // Draw grid
    tft.drawRect(40,25,20,20,color);
    tft.drawRect(70,25,20,20,color);
    tft.drawRect(100,25,20,20,color);

    //row2 
    tft.drawRect(40,55,20,20,color);
    tft.drawRect(70,55,20,20,color);
    tft.drawRect(100,55,20,20,color);
    
    //row3
    tft.drawRect(40,85,20,20,color);
    tft.drawRect(70,85,20,20,color);
    tft.drawRect(100,85,20,20,color);
}

void tic_tac_run()
{
    tft.fillScreen(ST7735_WHITE);
    auto  color = ST7735_BLACK;
    tft.setCursor(47,5);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_BLACK);
    tft.print("Tic Tac Toe");
    //row1

    tft.drawRect(40,25,20,20,color);
    tft.drawRect(70,25,20,20,color);
    tft.drawRect(100,25,20,20,color);

    //row2 
    tft.drawRect(40,55,20,20,color);
    tft.drawRect(70,55,20,20,color);
    tft.drawRect(100,55,20,20,color);
    
    //row3
    tft.drawRect(40,85,20,20,color);
    tft.drawRect(70,85,20,20,color);
    tft.drawRect(100,85,20,20,color);

    Potentiometer Potentiometer1; //get the knobs value
    tacEngine tacengine; // gives access to stored matrix value and matrix index 

    int prevy = 0;
    int prevx = 0;
    int prevknobvalue = 0;
    while (true)
    {

        char button = loopy();
        int knobvalue = Potentiometer1.getPotValue();
        auto y = tacengine.getpos().first; //new y value
        auto x = tacengine.getpos().second; //new x value

       //std::cout<<knobvalue<<endl; debugging for the potentiometer
        
        if(button == 'B') // moving forward 
        {
            prevx = x;
            prevy = y; // updates the old y value;
            tacengine.moveright(); // updates the x coordinate +1
            cout<< "Moved right"<<endl;
        }


        if(button == 'O')

        {
          bool recieved = tacengine.checkBox(y,x);
          if(recieved == true && tacengine.getTurns() % 2 != 0 ){
            tft.setCursor(47 + (x*30),30 + (y*30));
            tft.print('X'); 
          }else if(recieved == true && tacengine.getTurns() % 2 == 0 ){
            tft.setCursor(47 + (x*30),30 + (y*30));
            tft.print('O'); 
          }else if (recieved == false) {
            continue;
          }
        }
        

        if(knobvalue > prevknobvalue+8){ //moves the cursor down
          prevy = y; // updates the old y value;
          prevx = x; // updates the old y value;
          tacengine.moveup();
          cout<< "increasing"<<endl;
        }
        

        if(knobvalue < prevknobvalue-8){ //moves the cursor down
          prevy = y; // updates the old y value;
          prevx = x; // updates the old y value;
          tacengine.movedown();
          cout<< "decreasing"<<endl;
        }
        
         tft.drawRect(40 + (x*30),25 + (y*30),20,20,ST7735_RED); // box is highlighted 
        delay(100);
        tft.drawRect(40 + (prevx*30),25 + (prevy*30),20,20,ST7735_BLACK);
        // **Check for a win right after placing a move**
        if (tacengine.checkWinO() == true) {
            std::cout<< "X is the winner" << std::endl;
            tft.setCursor(5,115);
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
            tft.print("X wins");
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.print(" Press E to restart");
            button= loopy();
            if(button == 'E')
            {
              tacengine = tacEngine();
              Potentiometer1 = Potentiometer();
              resetGame();
              prevx = 0;
              prevy = 0;
            }
        }else if (tacengine.checkWinX() == true) {
          std::cout<< "O is the winner" << std::endl;
            tft.setCursor(5,115);
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
            tft.print("O wins");
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.print(" Press E to restart");
            button= loopy();
            if(button == 'E')
            {
              tacengine = tacEngine();
              Potentiometer1 = Potentiometer();
              resetGame();
              prevx = 0;
              prevy = 0;
            }
        }        
        

        //std::cout<< '(' << x << ',' << y << ')' << std::endl;
        //std::cout<< '(' << prevx << ',' << prevy << ')' << std::endl;

        prevknobvalue = knobvalue;
    }   
        
}