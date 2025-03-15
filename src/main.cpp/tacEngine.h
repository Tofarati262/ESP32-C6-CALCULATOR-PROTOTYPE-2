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

int move = 0;


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

    bool checkBox(int i , int j)

    {

        if (matrix[i][j] == ' ' && move == 0) // for first insertion 
        {
            matrix[i][j] == 'X';
            return true;
        } else if(matrix[i][j] == ' ' && move % 2 == 0) // for every even insertion
        {
            matrix[i][j] == 'O';
            return true;
        } else if(matrix[i][j] == ' ' && move % 2 >= 1) // for every oddd insertion
        {
            matrix[i][j] == 'x';
            return true;
        }else{
            return false;
        }

    }

    int getTurns()
    {
        return move;
    }

    pair<int,int> getpos()
    {
        return {position[0].first, position[0].second};
    }
};

void tic_tac_run();

#endif