/*
 * Copyright 2014 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef MAPA_H
#define MAPA_H

#define MAX_CONEXIONES 8


#include <vector>
#include <limits>
#include <SDL/SDL.h>
using namespace std;

 const int MAX_VALUE =  std::numeric_limits<int>::max()/100;
//const long int MAX_VALUE = 30000;
struct conexion
{
    int x, y;
    int conectax,conectay;
    long int peso;
	bool utilizado;
};

struct arista
{
    SDL_Rect nodo1;
    SDL_Rect nodo2;
};



class Mapa
{
public:
    Mapa();
    ~Mapa();
    bool isVisitado();
    void setVisitado(bool visitado);
    int getX();
    int getY();
    void setX(int x);


    void setY(int y);


    struct conexion arista[8];


private:

    bool visitado;
    int x,y;

};

#endif // MAPA_H
