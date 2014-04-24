#include "../include/bee.hpp"

bee::bee()
{
	file= "resources/sprites/bee.png";
	sprite= IMG_Load(file.c_str());
	if(!sprite)
	{
		cout << "Error con gold " << SDL_GetError()<< endl;
		exit(1);
	}
	
	cout << "Gold cargado exitosamente" <<endl;
	
	
	
	//load sprite frames
	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<4; ++j)
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
	this->map_height= map_height;
	this->map_width=map_width;
	
	status=STAND;
	obstaculo=0;
}

void bee::create()
{
	file= "resources/sprites/bee.png";
	sprite= IMG_Load(file.c_str());
	if(!sprite)
	{
		cout << "Error con gold " << SDL_GetError()<< endl;
		exit(1);
	}
	
	cout << "Gold cargado exitosamente" <<endl;
	
	
	
	//load sprite frames
	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<4; ++j)
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
	this->map_height= map_height;
	this->map_width=map_width;
	
	status=STAND;
	obstaculo=0;
}
