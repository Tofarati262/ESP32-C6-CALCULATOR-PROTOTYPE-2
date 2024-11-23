#include <iostream>
#include <stdexcept>

#define MAXBUFFER 20

class CALCSTACK {
private:
    int numberStack[MAXBUFFER];
    char operatorStack[MAXBUFFER];
    int numberTop;
    int operatorTop;

public:
    CALCSTACK() : numberTop(-1), operatorTop(-1) {}

    // Push a number onto the number stack
    void pushNumber(int number) {
        if (numberTop >= MAXBUFFER - 1) {
            throw std::overflow_error("Number stack overflow");
        }
        numberStack[++numberTop] = number;
    }

    // Peek at the top of the number stack
    int peekNumber() const {
        return numberStack[numberTop];
    }

    // Pop a number from the number stack
    int popNumber() {

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
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    // Evaluate the current expression
    void evaluate() {

        int b = popNumber();
        int a = popNumber();
        char op = popOperator();

        int result;
        switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            result = a / b;
            break;
        default:
            result = b;
        }

        pushNumber(result);
    }
};
