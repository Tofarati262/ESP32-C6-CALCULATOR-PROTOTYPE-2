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

bool verticalscan(char value, int index)
{

    for(int j= 0 ; j < 3 ; j++ )
    {
        if(matrix[j][index] != value)
        {
            return false;
        }
    }        
    return true;
}
    
bool horizontalscan(char value , int index)
{

    for(int j= 0 ; j < 3 ; j++ )
    {
        if(matrix[index][j] != value)
        {
            return false;
        }
    }        
    return true;
}

bool diagonalscan( char value, int index )
{

    if(index == 0)
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            if(matrix[i][i] != value)
            {
                return false;
            }
        }
    }else if (index ==2)
    {
        for(int i = 0; i < 3 ; i++)
        {
            if(matrix[i][2-i] != value)
            {
                return false;
            }
        }
    }

    return true;
}

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
          position[0].first = 2;
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
        
        if (matrix[i][j] == ' ' && move % 2 != 0) // for first insertion 
        {
            matrix[i][j] = 'X';
            move++;
            return true;
        }else if(matrix[i][j] == ' ' && move % 2 == 0) // for every even insertion
        {
            matrix[i][j] = 'O';
            move++;
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

    bool checkWinX()
    {
        for(int i = 0 ; i < 3; i++)
        {
            bool horizontal = horizontalscan('X', i);
            bool vertical = verticalscan('X', i );
            bool diagonal = false;
            if(i == 0 || i ==2)
            {
             diagonal = diagonalscan('X', i);
            }

            if(horizontal || vertical || diagonal)
            {
                return true;
            }
        }

        return false;
    }

    bool checkWinO()
    {
        for(int i = 0 ; i < 3; i++)
        {
            bool horizontal = horizontalscan('O', i);
            bool vertical = verticalscan('O', i );
            bool diagonal = false;
            if(i == 0 || i ==2)
            {
             diagonal = diagonalscan('O', i);
            }

            if(horizontal || vertical || diagonal)
            {
                return true;
            }
        }
        return false;
    }

};

void tic_tac_run();

#endif