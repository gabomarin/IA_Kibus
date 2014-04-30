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

#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <SDL/SDL_ttf.h>
#include <boost/lexical_cast.hpp>

#define CLICK 1
#define MOUSEOVER 1
#define MOUSEOUT 0


using namespace std;
using namespace boost;
class slider
{
public:
    slider(int width, int x, int y);
	slider(int width, int value, int x, int y, int min, int max);
    ~slider();
	int getValue();
	void setValue(int value);
	SDL_Surface * updateSlider();
	int getX();
	int getY();
    int getWidth();
	int getRealWidth();
	int handleEvents(SDL_Event event);
    void calculateValue();
	SDL_Rect * getFrame();
	
	
	
	
	
	
	
private:
    int value;
	SDL_Surface *bar;
	SDL_Surface *sliderImg;
	SDL_Surface *texto;
	SDL_Rect sliderPos;
	int width,x,y,realWidth;
	TTF_Font *font;
	SDL_Color textColor;
	int startClick,endClick; //posicion iniciarl y final para arrastre de slider
	bool clicked;
    int currentFrame;
	int min,max;
	SDL_Rect frame[2];
	
	
};

#endif // SLIDER_H
