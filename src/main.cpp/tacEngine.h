#ifndef tacEngine_h
#define tacEngine_h

#include <vector>
#include <iostream>

using namespace std;


class tacEngine
{
private:

char matrix[3][3]= 
{
    {' ', ' ',' '},
    {' ', ' ',' '},
    {' ', ' ',' '},
};

pair<int,int> position[1] =  {{0,0}};
    
public:
    void moveup(){
        position[0].first++;
    }

    void movedown(){
        position[0].first--;
    }

    void moveleft(){
        position[0].second--;
    }

    void moveright(){
        position[0].second++;
    }

    pair<int,int> getpos()
    {
        return {position[0].first, position[0].second};
    }
};

void tic_tac_run();

#endif