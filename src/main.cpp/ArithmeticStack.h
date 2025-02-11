#include <iostream>
#include <stdexcept>

#define MAXBUFFER 100

class CALCSTACK {
private:
    double numberStack[MAXBUFFER];
    char operatorStack[MAXBUFFER];
    int numberTop;
    int operatorTop;

public:
    CALCSTACK() : numberTop(-1), operatorTop(-1) {}

    int isEmpty(){
      if(numberTop== -1){
        return 0;
      }else{
        return 1;
      }
    }

    // Push a number onto the number stack
    void pushNumber(double  number) {
        if (numberTop >= MAXBUFFER - 1) {
            throw std::overflow_error("Number stack overflow");
        }
        numberStack[++numberTop] = number;
    }

    // Peek at the top of the number stack
    double peekNumber() const {
        return numberStack[numberTop];
    }

    // Pop a number from the number stack
    double  popNumber() {

        return numberStack[numberTop--];
    }

    // Push an operator onto the operator stack
    void pushOperator(char op) {
        if (operatorTop >= MAXBUFFER - 1) {
            throw std::overflow_error("Operator stack overflow");
        }
        operatorStack[++operatorTop] = op;
    }

    // Peek at the top of the operator stack
    char peekOperator() const {

        return operatorStack[operatorTop];
    }

    // Pop an operator from the operator stack
    char popOperator() {
        return operatorStack[operatorTop--];
    }

    // Check if a character is a valid operator
    bool isOperator(char ch) const {
        return ch == '+' || ch == '-' || ch == 'x' || ch == '/' || ch == '('|| ch =='P'|| ch =='S'|| ch =='^'|| ch =='A'|| ch =='C'|| ch =='.'|| ch =='G'|| ch =='N'|| ch =='D'|| ch =='S';
    }

    // Evaluate the current expression
    void evaluate() {

        double  b = popNumber();
        double a = popNumber();
        char op = popOperator();

        double  result;
        switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case 'x': result = a * b; break;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            result = a / b;
            break;
        default:
            result = b;
        }

        pushNumber(result);
    }


    int countDecimalPlaces(double number) {
    int count = 0;
    
    // Check if the number is already an integer
    if (number == (int)number) {
        return 0;
    }

    // Loop to count the digits after the decimal point
    while (number != (int)number) {
        number *= 10;
        count++;
    }

    return count;
    }
};
