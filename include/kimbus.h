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
#include <cstdlib>
#include <SDL/SDL.h>
#include <vector>
#include <fstream>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_ttf.h>
#include <ctime>

#include "hero.hpp"
#include "timer.hpp"
#include "button.hpp"
#include "slider.hpp"
#include "functions.hpp"


#define TILE_SIZE 32 	//tamaño de cada cuadro de la cuadricula
#define MAP_HEIGHT 17
#define MAP_WIDTH 22

#define WIDTH MAP_WIDTH*TILE_SIZE
#define HEIGHT (MAP_HEIGHT*TILE_SIZE)+(TILE_SIZE*3)
#define BPP 24

#define HOME 1
#define GRASS 2
#define TALL_GRASS 3
#define FLAG_1 4
#define FLAG_2 5
#define FLAG_3 6


#define TREE 4
#define ROCK 5
#define HERO 6






using namespace std;

typedef struct  coor
{
	int x,y;
}posicion;
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
	posicion pos;
    SDL_Surface* rock;
	int startx,starty;
    SDL_Rect posH;
	hero gold;
    SDL_Surface* water3;
    SDL_Surface* water2;
    SDL_Surface* water1;
	
	SDL_Surface* redAlpha;
	SDL_Surface *messagebox;
	SDL_Surface *texto;
	TTF_Font *font;
	SDL_Rect position;
	
	SDL_Rect selectedTile;
	SDL_Surface * selected;
	
	
	int mouse_x,mouse_y;
	SDL_Rect mouseTile;

	
	
	
	
	
public:
	
	kimbus();
	~kimbus();	
	//bool init_graphics();
	
	SDL_Surface * getScreen();
	void addToScreen(SDL_Surface * surface, int x, int y,SDL_Rect *clip);
	void updateScreen();
	bool mainloop();
	bool loadmap(int opc);
	void drawmap();
	
	bool loadTiles();
	void setHome();
	void initializeMap();
	void randomMap(int value);
	void setTile(int click, int tile, SDL_Rect* tilePos);
	posicion getHome();
	void savemap();
	void bresenham(int x1,int y1,int x2,int y2);
    void clearmap();
	void addToMap(SDL_Surface * surface, int x, int y,SDL_Rect *clip);
	

	
	
	
	
	
	
	
	
};



#endif // KIMBUS_H
