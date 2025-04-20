#ifndef CALCBUFFER_H
#define CALCBUFFER_H
#include<vector>
#include<iostream>


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
};

#endif