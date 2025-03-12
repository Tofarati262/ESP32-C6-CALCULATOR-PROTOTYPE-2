#ifndef tacEngine_h
#define tacEngine_h

#include <vector>
#include <iostream>

using namespace std;


class tacEngine
{
private:

bool matrix[3][3]= 
{
    {false, false,false},
    {false, false,false},
    {false, false,false},
};



pair<int,int> position[1] =  {{0,0}};
    
public:
    void moveup() {
        if (position[0].first < 2) {
            position[0].first++;
        } else if (position[0].first == 2 ) {
            position[0].first = 0;
        }
    }

    void movedown(){
        if(position[0].first > 0 )
        {
            position[0].first--;
        }else if(position[0].first == 0 )
        {
          position[0].first = 0;
        }
    }

    void moveleft(){
        position[0].second--;
    }

    void moveright(){
        position[0].second++;

        if(position[0].second > 2 )
        {
            position[0].second = 0;
        }
    }

    pair<int,int> getpos()
    {
        return {position[0].first, position[0].second};
    }
};

void tic_tac_run();

#endif