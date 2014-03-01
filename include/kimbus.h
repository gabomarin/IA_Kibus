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

#ifndef KIMBUS_H
#define KIMBUS_H


#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <vector>
#include <fstream>

#include "hero.hpp"
#include "timer.hpp"
#include "button.hpp"


#define TILE_SIZE 48 	//tamaño de cada cuadro de la cuadricula
#define MAP_HEIGHT 10
#define MAP_WIDTH 15

#define WIDTH MAP_WIDTH*TILE_SIZE
#define HEIGHT (MAP_HEIGHT*TILE_SIZE)+TILE_SIZE*3
#define BPP 24







using namespace std;

class kimbus
{
private:
	
	SDL_Surface *screen;
	SDL_Surface *tree,*grass,*mapsurface,*tallgrass,*textbox, *home;

	SDL_Rect dest;
	//SDL_Event event;
	int done;
	Uint8 *keys;
	vector <string> map;
	ifstream map_file;
	int homeX,homeY;
	
	
	
	
public:
	
	kimbus();
	~kimbus();	
	//bool init_graphics();
	
	SDL_Surface * getScreen();
	void addToScreen(SDL_Surface * surface, int x, int y,SDL_Rect *clip);
	void updateScreen();
	void mainloop();
	bool loadmap();
	void drawmap();
	
	bool loadTiles();
	void setHome();
	
	
	
	
	
	
	
};



#endif // KIMBUS_H
