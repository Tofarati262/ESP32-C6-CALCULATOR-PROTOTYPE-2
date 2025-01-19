#ifndef ARITHMETICSTACK_H
#define ARITHMETICSTACK_H
#include <iostream>
#include <stdexcept>

#define MAXBUFFER 200



class CALCSTACK {
private:
    double numberStack[MAXBUFFER];
    char operatorStack[MAXBUFFER];
    int numberTop = -1;
    int operatorTop = -1;

public:
    CALCSTACK() : numberTop(-1), operatorTop(-1) {}

    int isnumEmpty(){
      if(numberTop== -1){
        return 0;
      }else{
        return 1;
      }
    }

    int sizeofnumberstack(){
        return sizeof(numberStack);
    }

    int sizeofoperatorstack(){
        return sizeof(operatorTop);
    }

    bool isOperatorEmpty(){
        if(operatorTop == -1){
            return true;
        }else{
            return false;
        }
    }

    int order(char c){
        switch (c)
        {
            case '-': return 0; break;
            case '+': return 1; break;
            case '*': return 2; break;
            case '/': return 3; break;
            case '^': return 4; break;
            case ')': return 5; break;
            default: return -1; break;
        }
    }



    // Push a number onto the number stack
    void pushNumber(double  number) {
        if (numberTop >= MAXBUFFER - 1) {
            std::cout<< "Number Stack Overflow";
        }
        numberStack[numberTop++] = number;
        numberTop++;
    }

    // Peek at the top of the number stack
    double peekNumber() const {
        return numberStack[numberTop];
    }

    // Pop a number from the number stack
    double  popNumber() {

        return numberStack[numberTop--];
        numberTop--;
    }

    // Push an operator onto the operator stack
    void pushOperator(char op) {
        if (operatorTop >= MAXBUFFER - 1) {
           std::cout<<"Operator stack overflow";
        }
        operatorStack[++operatorTop] = op;
        operatorTop++;
    }

    // Peek at the top of the operator stack
    char peekOperator() const {
        if (operatorTop < 0) { // Check for an empty stack
            std::cout << "Error: Operator stack is empty, cannot peek.\n";
            return '\0'; // Default value to avoid out-of-bounds access
        }
        return operatorStack[operatorTop];
    }
    

    // Pop an operator from the operator stack
    char popOperator() {
        if (operatorTop < 0) { // Check for an empty stack
            std::cerr << "Error: Operator stack is empty, cannot pop.\n";
            return '\0'; // Default value to avoid out-of-bounds access
        }
        return operatorStack[operatorTop--];
    }
    

    // Check if a character is a valid operator
    bool isOperator(char ch) const {
        return ch == '+' || ch == '-' || ch == 'x' || ch == '/';
    }

    void evaluate(){
        char op1 = popOperator();
        char rightOperand = popNumber();
        char leftOperand = popNumber();

        while(isOperatorEmpty()==true){
            if(isOperatorEmpty()==true){
                char op2 = peekOperator();
                if(order(op1)>order(op2)){
                  finalevaluate(leftOperand,rightOperand,op1);
                }else if(op1 == '.'){
                    
                }else{
                pushNumber(leftOperand);
                pushNumber(rightOperand);
                pushNumber(op1);
                }
            }else{
                finalevaluate(leftOperand,rightOperand,op1);
            }
        }
    }
    // Evaluate the current expression
    void finalevaluate(double a, double b , char op) {


        double  result = 0.0;
        switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case 'x': result = a * b; break;
        case '/':
            if (b == 0) {
                std::cout<<"Division by zero";
                result = a / b;
            }
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

#endif

