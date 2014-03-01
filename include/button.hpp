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

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

using namespace std;


class button
{
private:
    bool visible;
    int y;
    int x;
	SDL_Surface * image;
	SDL_Event bEvent;
	
	
public:
	button(string src, int x, int y);
	button();
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	SDL_Surface * getImage();
	
};

#endif // BUTTON_H
