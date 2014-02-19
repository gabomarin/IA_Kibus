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

#include "../include/hero.hpp"

hero::hero()
{
	file= "resources/sprites/gold.png";
	sprite= IMG_Load(file.c_str());
	if(!sprite)
	{
		cout << "Error con gold " << SDL_GetError()<< endl;
		exit(1);
	}
	
	cout << "Gold cargado exitosamente" <<endl;
	
	
	
	//load sprite frames
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<4;++j)
		{
			frame[i][j].x=i*HERO_WIDTH;
			frame[i][j].y=j*HERO_HEIGHT;
			frame[i][j].w=HERO_WIDTH;
			frame[i][j].h=HERO_HEIGHT;
		}
	}
	
	animation_frame=1;
	direction=HERO_RIGHT;
	x_=0;
	y_=(HERO_HEIGHT-HERO_WIDTH)*-1;
	animation=false;
	

	status=STAND;

	
}



hero::~hero()
{
	SDL_FreeSurface(sprite);
}



SDL_Surface* hero::getSurface()
{
	SDL_Surface *frame;
	return sprite;
}



int hero::getX()
{
	return x_;

}

int hero::getY()
{
	return y_;
}

void hero::setX(int x)
{
	x_=x;
}

void hero::setY(int y)
{
	y_=y;
}


SDL_Rect * hero::getFrame()
{
	
	return &frame[animation_frame][direction];
}

int hero::getAnimationFrame()
{
	return animation_frame;
}


int hero::getDirection()
{
	return direction;
}

void hero::setAnimationFrame(int nFrame)
{
	 animation_frame=nFrame;
}

void hero::setDirection(int dir)
{
	direction=dir;
}


bool hero::getAnimation()
{
	return animation;
}

void hero::setAnimation(bool animate)
{
	animation=animate;
}

void hero::move()
{
	if(x_<0)
	{
		
	}
}

void hero:: handle_events(vector <string> map)
{

		//If a key was pressed
		if(status==STAND)
		{
			if( event.type == SDL_KEYDOWN )
			{
				//Set the velocity
				int dir=SDLK_RIGHT;
				switch(event.key.keysym.sym /*dir*/)
				{
					case SDLK_RIGHT: 
						if(x_/HERO_WIDTH<9)
						if((map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)+1))=='A')
						{
						
							//no hacer nada
						}
						else if(x_/HERO_WIDTH>8)
						{
							//no hacer nada
						}
						else
						{
							cout <<x_/HERO_WIDTH+1<<endl;
							direction=HERO_RIGHT;
							status=MOVEMENT;
							current_frame=0;
							animation_frame=0;
						}
						//x_ += HERO_WIDTH/4 ;
							
						;
					break;
					case SDLK_LEFT: 
						if(x_/HERO_WIDTH>0)
							if((map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)-1)=='A'))
							{
								
								//no hacer nada
							}
							else if(x_/HERO_WIDTH<=0)
							{
								//no hacer nada
							}
							else
							{
								cout <<x_/HERO_WIDTH+1<<endl;
								direction=HERO_LEFT;
								status=MOVEMENT;
								current_frame=0;
								animation_frame=0;
							}
					break;
					
					case SDLK_UP:
						
						if(y_/HERO_HEIGHT>0)
							if((map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))=='A'))
							{
								
								//no hacer nada
							}
						else if(y_/HERO_HEIGHT<=0)
						{
							
						}
						else
						{
							cout <<y_/HERO_HEIGHT+1<<endl;
							direction=HERO_UP;
							status=MOVEMENT;
							current_frame=0;
							animation_frame=0;
						}
					break;
					
					case SDLK_DOWN:
						 
						if(y_/HERO_WIDTH<7)
							if((map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH))=='A')
							{
								
								//no hacer nada
							}
							else if(y_/HERO_WIDTH>6)
							{
								//no hacer nada
							}
							else
							{
								cout <<x_/HERO_WIDTH+1<<endl;
								direction=HERO_DOWN;
								status=MOVEMENT;
								current_frame=0;
								animation_frame=0;
							}
						break;
					
				}
			}
		}
		
		if(status==MOVEMENT		)
		{
			//status=STAND;
			//animation_frame=1;
			int movement=0;
			if(current_frame<=7)
			{
				switch(current_frame)
				{
					case 0: case 4:
						animation_frame=2;
						break;
						
					case 1 :case 5:
						animation_frame=1;
						break;
						
					case 2:case 6:
						animation_frame=0;
						break;
						
					case 3:
						animation_frame=1;
						break;
					case 7:
						animation_frame=1;
						//movement=16;
						status=STAND;
						break;
				}
				switch(direction)
				{
					case HERO_DOWN:
						y_ += HERO_HEIGHT/8 -movement;
						break;
						
					case HERO_UP:
					y_ -= HERO_HEIGHT/8 -movement;
						break;
						
					case HERO_LEFT:
						x_ -= HERO_WIDTH/8 -movement;
						break;
						
					case HERO_RIGHT:
						x_ += HERO_WIDTH/8 -movement;
						break;
				}
				current_frame++;
			}
			
			

		
		}
	
}


bool hero::checkColision(vector <string> map)
{

	
	return false;
}



