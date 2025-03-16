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

bool diagonalscan( char value )
{
  bool mainDiagonal = (matrix[0][0] == value && matrix[1][1] == value && matrix[2][2] == value);
  bool antiDiagonal = (matrix[0][2] == value && matrix[1][1] == value && matrix[2][0] == value);
  return mainDiagonal || antiDiagonal;
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
            

            if(horizontal || vertical)
            {
                return true;
            }

        }
         return diagonalscan('X');
    }

    bool checkWinO()
    {
        for(int i = 0 ; i < 3; i++)
        {
            bool horizontal = horizontalscan('O', i);
            bool vertical = verticalscan('O', i );
            if(horizontal || vertical)
            {
              return true;
            }

        }
         return diagonalscan('O');

    }

};

void tic_tac_run();

#endif