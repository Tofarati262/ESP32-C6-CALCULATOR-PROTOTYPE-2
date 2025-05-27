#ifndef ERROR_H
#define ERROR_H

#include "DisplayInit.h"
#include <string>

using namespace std;
class Error
{

    private:

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

    public:



    bool findErrors(int *num_count  , int *operator_count, vector <char> *equation)
    {
    
      CALCSTACK checking;
    
      for(int i =0 ; i < equation->size() ; i++)
      {
        char current = (*equation)[i];
        char next = (*equation)[i + 1];

        if (checking.isOperator(current) && checking.isOperator(next)) {
            display_error("SYNTAX");
            return true;
        }

      }

      if(num_count == 0)
      {
        display_error("SYNTAX");
        return true;
      }else if(num_count == operator_count )
      {
        display_error("SYNTAX");
        return true;
      }else if(operator_count > num_count )
      {
        display_error("SYNTAX");
        return true;
      }


        

        return false;
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