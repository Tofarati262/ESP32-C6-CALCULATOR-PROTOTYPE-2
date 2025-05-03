#ifndef CALCBUFFER_H
#define CALCBUFFER_H
#include<vector>
#include<iostream>
#include <cmath>
#include <string>


using namespace std;
class calcBuffer
{
private:
    vector<pair<vector<char>,int>> equationholder;    
public:

unsigned long long  factorialcalc(int *ptrvalue)
{
    unsigned long long  returnvalue = 1;
    while (*ptrvalue > 1)
    {
        returnvalue *= *ptrvalue;
        (*ptrvalue)--;
    }
    return returnvalue;
}
    
    void pushequation( vector<char> equation, int answer)
    {
      equationholder.push_back({equation,answer});
    }

    void clearequationholder()
    {
      equationholder.clear();
    }

    void logEquations()
    {
      for(auto& equation : equationholder)
      {
        for (char c : equation.first)
        {
          std::cout << c ;
        }

        cout << " =" << equation.second <<endl;
        cout << "\n" << endl;
      }
    }

    int answer()
    {
        auto& answer = equationholder.back().second;
        cout << answer << endl;
        return answer;
    }

    vector<char> getEquation(int index)
    {
      return equationholder[index].first;
    }

    pair<int ,int> countValues (vector <char> equations)
    {
      int numcount = 0;
      int operatorcount = 0;


      for( char value : equations)
      {
        std::cout<< value << std::endl;
        if(value >= '0' && value <= '9')
        {
          numcount++;
        }

        if(value == 'X' || value == '/' || value == '-' || value == '+')
        {
          operatorcount++;
        }
      }

      return{numcount, operatorcount};
    }

    std::vector<char> Specialfunctions(std::vector<char> equation) {
    double angle = 0;
    int j = 0;

    for (int i = 0; i < equation.size(); i++) {
        // sin
        if (i + 3 < equation.size() && equation[i] == 's' && equation[i + 1] == 'i' && equation[i + 2] == 'n' && equation[i + 3] == '(') {
            j = i + 4;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for sin\n";
                return equation;
            }

            angle = std::stod(numberStr);
            double result = sin(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1; // restart loop
        }

        // cos
        else if (i + 3 < equation.size() && equation[i] == 'c' && equation[i + 1] == 'o' && equation[i + 2] == 's' && equation[i + 3] == '(') {
            j = i + 4;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for cos\n";
                return equation;
            }

            angle = std::stod(numberStr);
            double result = cos(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // tan
        else if (i + 3 < equation.size() && equation[i] == 't' && equation[i + 1] == 'a' && equation[i + 2] == 'n' && equation[i + 3] == '(') {
            j = i + 4;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for tan\n";
                return equation;
            }

            angle = std::stod(numberStr);
            double result = tan(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // ln
        else if (i + 2 < equation.size() && equation[i] == 'l' && equation[i + 1] == 'n' && equation[i + 2] == '(') {
            j = i + 3;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for ln\n";
                return equation;
            }

            angle = std::stod(numberStr);
            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for ln\n";
                return equation;
            }

            double result = log(angle); // ln is natural log
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // log (assumed base 10)
        else if (i + 3 < equation.size() && equation[i] == 'l' && equation[i + 1] == 'o' && equation[i + 2] == 'g' && equation[i + 3] == '(') {
            j = i + 4;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for log\n";
                return equation;
            }

            angle = std::stod(numberStr);
            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for log\n";
                return equation;
            }

            double result = log10(angle); // common log
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;

        //sqrt

        }else if (i + 4 < equation.size() && equation[i] == 's' && equation[i + 1] == 'q' && equation[i + 2] == 'r' && equation[i + 3] == 't' && equation[i + 4] == '(')
        {
            j = i + 5;
            std::string numberStr;

            while (j < equation.size() && (isdigit(equation[j]) || equation[j] == '.')) {
                numberStr += equation[j];
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis for log\n";
                return equation;
            }

            angle = std::stod(numberStr);
            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for log\n";
                return equation;
            }

            double result = sqrt(angle); // common log
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }else if (equation[i] == '!') {
            std::string value;
            int j = i - 1;

            // Collect digits backward
            while (j >= 0 && isdigit(equation[j]) && value.size() < 3) {
                value += equation[j];
                j--;
            }

            if (value.empty()) {
                std::cout << "Syntax Error" << std::endl;
                return equation;
            }

            std::reverse(value.begin(), value.end());  // Fix digit order
            int number = std::stoi(value);
            if(number <= 20){
                unsigned long long result = factorialcalc(&number);
    
                // Erase number and '!' from equation
                equation.erase(equation.begin() + j + 1, equation.begin() + i + 1);
    
                // Insert result back
                std::string resultStr = std::to_string(result);
                equation.insert(equation.begin() + j + 1, resultStr.begin(), resultStr.end());
    
                return equation; // Only one factorial processed at a time
            }else{
                std::cout << "Value is too big" << std::endl;
                return equation;
            }
        }
    }

    return equation;
  }
};

#endif