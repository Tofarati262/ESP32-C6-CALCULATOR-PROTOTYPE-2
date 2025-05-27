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
    vector<pair<vector<char> , double>> equationholder;    
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
    
    void pushequation( vector<char> equation, double answer)
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

    double answer()
    {
        auto& answer = equationholder.back().second;
        cout << answer << endl;
        return answer;
    }

    pair<vector<char>,double> getEquation(int index)
    {
      return {equationholder[index].first, equationholder[index].second};
    }

pair<int ,int> countValues (vector <char> equation)
{
    int numCount = 0;
    int operatorCount = 0;

    std::string token;
    for (size_t i = 0; i < equation.size(); ++i) {
        char c = equation[i];

        if (std::isdigit(c) || c == '.') {
            token += c;
        } else {
            // End of a number
            if (!token.empty()) {
                ++numCount;
                token.clear();
            }

            // Check if it's an operator
            if (c == '+' || c == '-' || c == '/' || c == 'X' || c == '*') {
                ++operatorCount;
            }
        }
    }

    // If equation ends with a number
    if (!token.empty()) {
        ++numCount;
    }

    return {numCount, operatorCount};
}

    std::vector<char> Specialfunctions(std::vector<char> equation) {
    double angle = 0;
    int j = 0;

    for (int i = 0; i < equation.size(); i++) {

        //e
        if(equation[i] == 'e'){
            std::string resultstr = "2.71828";
            equation.erase(equation.begin() + i);
            equation.insert(equation.begin() + i,resultstr.begin(), resultstr.end() );
            i = -1;
        }

        // sin

        else if (i + 3 < equation.size() && equation[i] == 's' && equation[i + 1] == 'i' && equation[i + 2] == 'n' && equation[i + 3] == '(') {
            j = i + 4;
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic
            double result = sin(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // cos

        else if (i + 3 < equation.size() && equation[i] == 'c' && equation[i + 1] == 'o' && equation[i + 2] == 's' && equation[i + 3] == '(') {
            j = i + 4;
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic
            double result = cos(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // tan

        else if (i + 3 < equation.size() && equation[i] == 't' && equation[i + 1] == 'a' && equation[i + 2] == 'n' && equation[i + 3] == '(') {
            j = i + 4;
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic

            Error displayerr;

            if (angle == 90) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for log\n";
                displayerr.display_error("DOMAIN");
                return equation;
            }

            double result = tan(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        // ln

        else if (i + 2 < equation.size() && equation[i] == 'l' && equation[i + 1] == 'n' && equation[i + 2] == '(') {
            j = i + 3;
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic

            Error displayerr;

            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for ln\n";
                displayerr.display_error("DOMAIN");
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
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic

            Error displayerr;

            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for log\n";
                displayerr.display_error("DOMAIN");
                return equation;
            }

            double result = log10(angle); // common log
            std::string resultStr = std::to_string(result);

            equation.erase(equation.begin() + i, equation.begin() + j + 1);
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());
            i = -1;
        }

        //sqrt

        else if (i + 4 < equation.size() && equation[i] == 's' && equation[i + 1] == 'q' && equation[i + 2] == 'r' && equation[i + 3] == 't' && equation[i + 4] == '(')
        {
            j = i + 5;
            int openParens = 1;
            std::vector<char> innerVec;

            while (j < equation.size() && openParens > 0) {
                if (equation[j] == '(') openParens++;
                else if (equation[j] == ')') openParens--;

                if (openParens > 0) {
                    innerVec.push_back(equation[j]);
                }
                j++;
            }

            innerVec = Specialfunctions(innerVec); // Recursive eval
            std::string innerStr(innerVec.begin(), innerVec.end());

            CALCSTACK nested_equation;
            angle = nested_equation.EvaluateExpression(innerStr); // NEW: Handles arithmetic\

            Error displayerr;

            if (angle <= 0) {
                std::cout << "ERROR: DOMAIN OUT OF BOUNDS for log\n";
                displayerr.display_error("DOMAIN");
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