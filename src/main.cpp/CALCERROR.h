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
        tft.setCursor(10, 30);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

        tft.print("1:");

        tft.setCursor(40, 30);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print("Quit");


        tft.setCursor(10, 60);
        tft.setTextSize(1);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

        tft.print("2:");

        tft.setCursor(40, 60);
        tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
        tft.print("Goto");
    }

    int display_error( string errormessage)
    {
      tft.fillScreen(ST7735_WHITE);
      char key;

      while((key = loopy()) != '1' && (key = loopy()) != '2'){

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

      if(key == '1')
      {

      }else if (key == '2')
      {
        
      }
        

        tft.fillScreen(ST7735_WHITE);
        return 0;
    }
};

#endif