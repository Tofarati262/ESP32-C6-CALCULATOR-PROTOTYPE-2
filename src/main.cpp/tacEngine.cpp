#include "tacEngine.h"
#include "DisplayInit.h"


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

    Potentiometer Potentiometer; 
    tacEngine tacengine; 

    int prevy = 0;
    int prevx = 0;

    while (true)
    {
        int knobvalue = Potentiometer.getPotValue();
        auto y = tacengine.getpos().first; //new y value
        auto x = tacengine.getpos().second; //new x value

        
        if(knobvalue > Potentiometer.getPotValue() &&  x < 2) // moving forward 
        {
            tacengine.moveright(); // updates the x coordinate +1
        }
        if(knobvalue < Potentiometer.getPotValue() && x > 0) 
        {
            tacengine.moveleft();
        }


        tft.drawRect(40 + (x*30),25 + (y*30),20,20,ST7735_YELLOW); // box is highlighted 
        tft.drawRect(40 + (prevx*30),25 + (prevy*30),20,20,color);


        std::cout << "in game engine"<<std::endl;
        prevy = y;
        prevx = x;
    }   
        
}