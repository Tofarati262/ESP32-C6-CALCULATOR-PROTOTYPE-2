#include "tacEngine.h"
#include "DisplayInit.h"
#include "Exiomatrix.h"

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

    Potentiometer Potentiometer; //get the knobs value
    tacEngine tacengine; // gives access to stored matrix value and matrix index 

    int prevy = 0;
    int prevx = 0;
    int prevknobvalue = 0;
    while (true)
    {
        char button = loopy();
        int knobvalue = Potentiometer.getPotValue();
        auto y = tacengine.getpos().first; //new y value
        auto x = tacengine.getpos().second; //new x value

        std::cout<<knobvalue<<endl;
        
        if(button == 'B') // moving forward 
        {
            prevx = x;
            prevy = y; // updates the old y value;
            tacengine.moveright(); // updates the x coordinate +1
            cout<< "Moved right"<<endl;
        }

        

        if(knobvalue > prevknobvalue+4){ //moves the cursor down
          prevy = y; // updates the old y value;
          prevx = x; // updates the old y value;
          tacengine.moveup();
          cout<< "increasing"<<endl;
        }
        

        if(knobvalue < prevknobvalue-1){ //moves the cursor down
          prevy = y; // updates the old y value;
          prevx = x; // updates the old y value;
          tacengine.movedown();
          cout<< "decreasing"<<endl;
        }
        
       

        std::cout<< '(' << x << ',' << y << ')' << std::endl;
        std::cout<< '(' << prevx << ',' << prevy << ')' << std::endl;

        prevknobvalue = knobvalue;

        tft.drawRect(40 + (x*30),25 + (y*30),20,20,ST7735_RED); // box is highlighted 
        delay(100);
        tft.drawRect(40 + (prevx*30),25 + (prevy*30),20,20,ST7735_BLACK);
        delay(50);
    }   
        
}