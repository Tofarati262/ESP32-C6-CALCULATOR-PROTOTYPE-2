#ifndef ERROR_H
#define ERROR_H

#include "DisplayInit.h"
#include <string>

using namespace std;
class Error
{
    public:

    void write_options()
    {
        tft.setCursor(10, 15);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

        tft.print("1:");

        tft.setCursor(15, 15);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print("Quit");

        tft.print("1:");

         tft.setCursor(10, 35);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

        tft.print("2:");

        tft.setCursor(15, 35);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print("Goto");
    }

    int display_error( string errormessage)
    {

        if(errormessage == "DOMAIN")
        {

            tft.setCursor(40, 5);
            tft.setTextSize(1);
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.print("DOMAIN");

            write_options();

            tft.setCursor(60, 5);

            tft.print("Value entered is not allowed in the function or domain. ");

            
        }else if(errormessage == "SYNTAX")
        {
            tft.setCursor(40, 5);
            tft.setTextSize(1);
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.print("SYNTAX");

            write_options();

            tft.setCursor(60, 5);

            tft.print("Incorrect Syntax entered. ");
        }

        

        return 0;
    }
};

#endif