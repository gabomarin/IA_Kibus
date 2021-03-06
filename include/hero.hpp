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

#ifndef HERO_H
#define HERO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <boost/concept_check.hpp>

#include "functions.hpp"

#define MAX_FRAMES 3	/*Numero maximo de frames que tendra la animacion de
							algun estado del personaje*/
#define NUM_DIRECTIONS 4   /*Numero maximo de direcciones posibles que tiene el personaje, arriba, abajo,izquierda,derechs*/


#define HERO_DOWN 0
#define HERO_LEFT 1
#define HERO_UP 2
#define HERO_RIGHT 3
#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_LEFT 6
#define DOWN_RIGHT 7

#define HERO_WIDTH 32
#define HERO_HEIGHT 32

#define STAND 0
#define MOVEMENT 1


SDL_Event event;
using namespace std;

class hero
{
public:
    hero(int map_width, int map_height);
	hero();
    ~hero();
    SDL_Surface * getSurface();
	int getDirection();
	void setDirection(int dir);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	SDL_Rect *getFrame();
	
	void  setAnimationFrame(int nFrame);
    bool getAnimation();
    void setAnimation(bool animate);
	int getAnimationFrame();
	
	void move();
	   int handle_events(vector< string >& map);
    void show();
	bool checkColision(vector <string > map);
	bool animate_stack();
	void create(int map_width, int map_height, int posx, int posy);
	void pushLine(int x, int y);
	SDL_Rect popLine();
	int getLineX();//regresan el primer elemento de la lista
	int getLineY();
    void printList();
	void dropList();
    int calculateDirection();
	void bresenham(int x1, int y1, int x2, int y2);
	void insertFirst(int x, int y);
	void printMap(vector <string> map);
    void setHouse(int posx, int posy);
	void setLastPosition(int x, int y);
    void setBanderin(vector< string >& map, int posicion);
	
private:
	
	string file;
	SDL_Surface *sprite;
	SDL_Rect frame[MAX_FRAMES][NUM_DIRECTIONS],lastPosition;
	int lastp;
	int direction,animation_frame,current_frame;
	int x_,y_;
	int destx,desty;
	bool animation;
	
	SDL_Event gEvent;
	int status;
	int map_height,map_width;
	vector <int> movement_stack;
	vector <SDL_Rect> line_stack;
	int obstaculo;
	//int frame_index[MAX_STATE][MAX_FRAMES];

	

};

#endif // HERO_H
