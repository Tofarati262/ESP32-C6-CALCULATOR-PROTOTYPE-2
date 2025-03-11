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

    while (true)
    {
        delay(1000);

        char button = loopy();
        int knobvalue = Potentiometer.getPotValue();
        auto y = tacengine.getpos().first; //new y value
        auto x = tacengine.getpos().second; //new x value

        std::cout<<knobvalue<<endl;
        prevx = x;

        if(button == 'B') // moving forward 
        {
            tacengine.moveright(); // updates the x coordinate +1
            cout<< "Moved right"<<endl;
        }

        prevy = y; // updates the old y value;

        if(knobvalue > Potentiometer.getPotValue() + 4 ){ //moves the cursor down
            tacengine.movedown();
            cout<< "increasing"<<endl;
        }
    
        if(knobvalue < Potentiometer.getPotValue() - 4 ){ //moves the cursor up
            tacengine.moveup();
            cout<< "decreasing"<<endl;
        }


        auto y = tacengine.getpos().first; //new y value
        auto x = tacengine.getpos().second; //new x value

        tft.drawRect(40 + (x*30),25 + (y*30),20,20,ST7735_RED); // box is highlighted 
        tft.drawRect(42 + (prevx*30),27 + (prevy*30),20,20,ST7735_BLACK);
    }   
        
}