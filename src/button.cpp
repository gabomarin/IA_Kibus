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

#include "../include/button.hpp"


button::button()
{
	
}

button::button(string src, int x,int y){
	
	image= IMG_Load(src.c_str());
	if(!image)
	{
		cout <<"No se pudo cargar el sprite " << SDL_GetError() << endl;
	}
	this->x=x;
	this->y=y;
	visible=true;
	
}

int button:: getX()
{
	return x;	
}

int button::getY()
{
	return y;
}


void button:: setX(int x)
{
	this->x=x;
	
}

void button::setY(int y)
{
	this->y=y;
}

SDL_Surface * button::getImage()
{
	return image;
}