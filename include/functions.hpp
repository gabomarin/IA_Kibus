
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;



int krandom(int maximo)
{
    int resultado=0;
    for(int i=0; i<maximo; i++)
    {
        int total=rand()%2;

        resultado+= total;
    }
    //cout <<"resultado: " << resultado;
    return resultado;

}


#endif
