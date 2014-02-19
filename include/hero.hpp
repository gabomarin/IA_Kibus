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

#define MAX_FRAMES 3	/*Numero maximo de frames que tendra la animacion de
							algun estado del personaje*/
#define NUM_DIRECTIONS 4   /*Numero maximo de direcciones posibles que tiene el personaje, arriba, abajo,izquierda,derechs*/


#define HERO_DOWN 0
#define HERO_LEFT 1
#define HERO_UP 2
#define HERO_RIGHT 3

#define HERO_WIDTH 64
#define HERO_HEIGHT 64

#define STAND 0
#define MOVEMENT 1


SDL_Event event;
using namespace std;

class hero
{
public:
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
	void handle_events(vector <string> map);
    void show();
	bool checkColision(vector <string > map);
	
	
	
private:
	
	string file;
	SDL_Surface *sprite;
	SDL_Rect frame[MAX_FRAMES][NUM_DIRECTIONS];
	int direction,animation_frame,current_frame;
	int x_,y_;
	bool animation;
	
	SDL_Event gEvent;
	int status;
	//int frame_index[MAX_STATE][MAX_FRAMES];
	
	
	
		
	

};

#endif // HERO_H
