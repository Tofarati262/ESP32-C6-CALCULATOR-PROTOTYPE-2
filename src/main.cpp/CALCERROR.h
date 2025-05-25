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
        tft.setCursor(10, 50);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

        tft.print("1:");

        tft.setCursor(40, 50);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print("Continue");
    }

    int display_error( string errormessage)
    {
      tft.fillScreen(ST7735_WHITE);
      char key;

      while((key = loopy()) != '1'){

        if(errormessage == "DOMAIN")
        {

            tft.setCursor(60, 5);
            tft.setTextSize(1);
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
            tft.print("DOMAIN");

            write_options();

            tft.setCursor(5, 80);

            tft.print("Value entered is not allowed in the function or domain. ");

            
        }else if(errormessage == "SYNTAX")
        {
            tft.setCursor(60, 5);
            tft.setTextSize(1);
            tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
            tft.print("SYNTAX");

            write_options();

            tft.setCursor(5, 80);

            tft.print("Incorrect Syntax entered. ");
        }

      }


        

        tft.fillScreen(ST7735_WHITE);
        return 0;
    }
};

#endif