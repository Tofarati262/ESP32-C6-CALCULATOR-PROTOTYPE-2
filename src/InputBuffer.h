#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H
#include "string.h"
#include <iostream>
#include <vector>
#define MAXBUFFER 200
int counter= 0;

class InputBuffer
{
private:
    std::vector<std::string> Inputstrings;
    double Result[MAXBUFFER];
    int Index = -1;
    std::vector<double> results;
    std::vector<int> accuracys;
public:
    void PushInput(std::string c, double result, int accuracy);
    double RetrieveInput();
};

void InputBuffer::PushInput(std::string c,double result, int accuracy)
{
    Inputstrings.push_back(c);
    results.push_back(result);
    accuracys.push_back(accuracy);
    counter++; 
}

double InputBuffer::RetrieveInput()
{
    return (results.pop_back(),accuracys.pop_back(),Inputstrings.pop_back());

}



#endif