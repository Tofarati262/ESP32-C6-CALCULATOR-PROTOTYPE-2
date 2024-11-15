#include "Exiomatrix.h"


void Setupkeypad(){
    //INITIALIZING columns
    Set_EXIO(TCA9554_EXIO1,1)
    Set_EXIO(TCA9554_EXIO2,1)
    Set_EXIO(TCA9554_EXIO3,1)
    Set_EXIO(TCA9554_EXIO4,1)
    Set_EXIO(TCA9554_EXIO5,1)

    //initializing rows 
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(18,OUTPUT);
    pinMode(19,OUTPUT);
}

char Scankeypad(){

    char hexaKeys[1][5] = {
 
        {'C', 'O', 'M', 'R', '='},      // Row 1: Clear and hold to clear entry, math button: {degrees, absolute value,modulus}, Mode, Recall, Equals
        /*({'B', 'L', '(', ')', 'T'},      // Row 2: Backspace, Logarithm, Open Parenthesis, Close Parenthesis, Trigonometric
        {'F', 'P', '7', '8', '9'},      // Row 3: Factorial, Pi, 7, 8, 9
        {'X', '/', 'S', '4', '5'},      // Row 4: Multiplication, Division, Square root, 4, 5
        {'6', '+', '-', '^', '1'},      // Row 5: 6, Addition, Subtraction, Exponentiation, 1
        {'2', '3', 'A', '0', '.'},      // Row 6: 2, 3, Trig Functions, 0, Decimal
        {'G', 'N', 'D', 'Q', 'R'},      // Row 7: Log base-10, Natural Log, Degrees toggle, Constant (Euler's number), square root)*/ 
    };
    for(int i = 0, i < 8, ++ ){

        for(int j = 0, j < 1, j++){

        }
    }

};