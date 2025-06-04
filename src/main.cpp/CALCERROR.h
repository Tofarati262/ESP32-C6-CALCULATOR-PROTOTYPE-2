#ifndef ERROR_H
#define ERROR_H

#include "DisplayInit.h"
#include <string>
#include <algorithm>

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

    bool isdigits(char value)
    {

      return value >= '0' && value <= '9';
      
    }

    public:



    bool findErrors(int num_count  , int operator_count, vector <char> equation)
    {
    
      CALCSTACK checking;
    
      for(int i =0 ; i < equation.size() - 1; i++)
      {
        char current = equation[i];
        char next = equation[i + 1];

        if (checking.isOperator(current) == true && checking.isOperator(next) == true) {

          display_error("SYNTAX");
          std::cout << "Executed: double operator\n";
          return true;
        }

        if (isdigits(current) == true && (checking.isOperator(next) == false && next != ')')) {

          display_error("SYNTAX");
          std::cout << "Digit followed " << current << " by invalid number "<< next << "\n";
          return true;
        }

      }
       

      if(num_count == 0)
      {
        display_error("SYNTAX");
        cout << "Error check 1 triggered" << "\n";
        return true;

      }else if(num_count == operator_count )
      {
        display_error("SYNTAX");
        cout << "Error check 2 triggered" << "\n";
        return true;

      }else if(operator_count > num_count )
      {
        display_error("SYNTAX");
        cout << "Error check 3 triggered" << "\n";
        return true;

      }

      return false;
    }

    
    void display_error( string errormessage)
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
    }
};

#endif