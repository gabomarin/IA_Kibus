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
	for(int i=0;i<2;++i)
	{

		frame[i].x=i*image->w/2;
		frame[i].y=0;
		frame[i].w=image->w/2;
		frame[i].h=image->w/2;
		
	}
	currentFrame=MOUSEOUT;
	
}

button:: ~button()
{
	SDL_FreeSurface(image);
	
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

int button::handleEvents(SDL_Event event)
{
	int mouse_x,mouse_y; //posicion del mouse
	if( event.type == SDL_MOUSEMOTION ) { //Get the mouse offsets 
		mouse_x = event.motion.x; 
		mouse_y = event.motion.y;
		//If the mouse is over the button 
		if( ( mouse_x > x ) && (mouse_x < x + (image->w/2) ) && ( mouse_y > y ) && ( mouse_y < y + (image->h) ) ) 
		{ //Set the button sprite 
			//clip = &clips[ CLIP_MOUSEOVER ];
			currentFrame=MOUSEOVER;
			
			
		} 
		//If not 
		else { 
			//Set the button sprite 
			//clip = &clips[ CLIP_MOUSEOUT ]; 
			currentFrame=MOUSEOUT;
			
		} 
		
	}
	
	if( event.type == SDL_MOUSEBUTTONDOWN ) 
	{ 
		//If the left mouse button was pressed 
		if( event.button.button == SDL_BUTTON_LEFT ) 
		{
			
			//Get the mouse offsets
			mouse_x = event.button.x;
			mouse_y = event.button.y; 
			//If the mouse is over the button 
			if( ( mouse_x > x ) && (mouse_x < x + image->w/2 ) && ( mouse_y > y ) && ( mouse_y < y + (image->h) ) ) 
			{ //Set the button sprite 
				cout << "click en el boton" <<endl;
				return CLICK;
				
			} 
			
		} 
		
	}
	
	
	return 0;
}


SDL_Rect * button::getFrame()
{
	return &frame[currentFrame];
}



int button::getHeight()
{
	return image->h;
}


int button::getWidth()
{
	return image->w;
}
