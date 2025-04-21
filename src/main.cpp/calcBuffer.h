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

     std::vector<char> functions(std::vector<char> equation) {
    double angle = 0;
    int j = 0;
    int appendindex = 0;

    for (int i = 0; i < equation.size(); i++) {
        if (equation[i] == 's' && equation[i + 1] == 'i' && equation[i + 2] == 'n' && equation[i + 3] == '(') {
            angle = 0;
            j = i + 4;

            // Read number until ')'
            while (j < equation.size() && equation[j] >= '0' && equation[j] <= '9') {
                angle = angle * 10 + (equation[j] - '0');
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis\n";
                return equation;
            }

            double result = sin(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result); // convert to string

            // Remove from 's' to ')'
            equation.erase(equation.begin() + i, equation.begin() + j + 1);

            // Insert result characters into the equation
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());

            return equation;
          }else if(equation[i] == 'c' && equation[i + 1] == 'o' && equation[i + 2] == 's' && equation[i + 3] == '(')
          {
            angle = 0;
            j = i + 4;

            // Read number until ')'
            while (j < equation.size() && equation[j] >= '0' && equation[j] <= '9') {
                angle = angle * 10 + (equation[j] - '0');
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis\n";
                return equation;
            }

            double result = cos(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result); // convert to string

            // Remove from 's' to ')'
            equation.erase(equation.begin() + i, equation.begin() + j + 1);

            // Insert result characters into the equation
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());

            return equation;

          }else if(equation[i] == 't' && equation[i + 1] == 'a' && equation[i + 2] == 'n' && equation[i + 3] == '(')
          {
            angle = 0;
            j = i + 4;

            // Read number until ')'
            while (j < equation.size() && equation[j] >= '0' && equation[j] <= '9') {
                angle = angle * 10 + (equation[j] - '0');
                j++;
            }

            if (j >= equation.size() || equation[j] != ')') {
                std::cout << "FAILURE: Expected closing parenthesis\n";
                return equation;
            }

            double result = tan(angle * M_PI / 180.0);
            std::string resultStr = std::to_string(result); // convert to string

            // Remove from 's' to ')'
            equation.erase(equation.begin() + i, equation.begin() + j + 1);

            // Insert result characters into the equation
            equation.insert(equation.begin() + i, resultStr.begin(), resultStr.end());

            return equation;

          }
      
      }

      std::cout << "FAILURE: SYNTAX ERROR or no 'sin('\n";
      return equation;
  }
};

#endif