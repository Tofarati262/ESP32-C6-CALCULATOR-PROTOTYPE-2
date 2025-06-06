#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <map>

using namespace std;

#define MAXBUFFER 100
#define MAXEQUATIONS 10

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
      }else if( numberTop == 0)
      {
        return 1;
      }else{
        return 2;
      }
    }



    bool isOperatorEmpty()
    {
      if(operatorTop  == -1)
      {
        return true;
      }else if (operatorTop  > -1){
        return false;
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
    bool isOperator(char ch){
        switch(ch)
        {
          case '+': return true; break;
          case '-': return true; break;
          case '/': return true; break;
          case 'x': return true; break;
          case '^': return true; break; 

          default: 
          return false;
          break;
        }
    }

    // Evaluate the current expression

    double precedence( char value)
    {
        switch (value)
        {
        
        case '^': return 3; break;
        case '/': return 2; break;
        case 'x': return 2; break;
        case '+': return 1; break;
        case '-': return 1; break;
        
        default:
            return -1;
            break;
        }
    }

    void evaluate() {

            double  b = popNumber();
            double a = popNumber();
            char op = popOperator();

            std::cout << "This is the value of a: " << a << "\n";
            std::cout << "This is the value of b: " << b << "\n";
            std::cout << "This is the value of the operator: " << op << "\n";

            double  result;
            switch (op) {
            case '^': result = pow(a,b); pushNumber(result); break;
            case '+': result = a + b;pushNumber(result); break;
            case '-': result = a-b;pushNumber(result); break;
            case 'x': result = a * b;pushNumber(result); break;
            case '/':
                if (b == 0)
                { 
                  throw std::runtime_error("Division by zero");
                }
                else
                {
                  result = a / b;
                  pushNumber(result);
                }
                break;
            default:
                result = b;
                pushNumber(result);
            }

             std::cout << "This is the result: " << result << "\n";
    }

    //recursive function 

    double EvaluateExpression(const std::string& expr) {
    std::istringstream input(expr);
    std::stack<double> values;
    std::stack<char> ops;
    std::map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^',3}};

    auto apply_op = [](double a, double b, char op) -> double {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case 'x': return a * b;
            case '/': return a / b;
            case '^': return pow(a,b);
        }
        return 0;
    };

    double num;
    char op;
    while (input >> num) {
        values.push(num);
        while (input >> op) {
            while (!ops.empty() && precedence[ops.top()] >= precedence[op]) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char prev_op = ops.top(); ops.pop();
                values.push(apply_op(a, b, prev_op));
            }
            ops.push(op);
            break;
        }
    }

    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char prev_op = ops.top(); ops.pop();
        values.push(apply_op(a, b, prev_op));
    }

    return values.top();
}
};
