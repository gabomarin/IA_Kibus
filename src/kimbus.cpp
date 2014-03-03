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

#include "../include/kimbus.h"

#include <string>
#include <cstdlib>

using namespace std;
kimbus::kimbus()
{
	//Start SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 
	SDL_WM_SetCaption( "Mundo de kimbus", NULL );
	SDL_WM_SetIcon(SDL_LoadBMP("resources/sprites/icon.bmp"),NULL);
	//cout <<SDL_GetError();

	putenv("SDL_VIDEO_CENTERED=1"); 
	//Set up screen 
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE );
	if(!screen)
	{
		cout << "Error al iniciar SDL. " << SDL_GetError()<< endl;
		exit(1);
		
	}
	
	else if(loadmap()==false)
	{
		exit(1);
	}
	
	else if(!loadTiles())
	{
		exit(1);
	}
	else
	{
		cout << "Mundo de Kimbus Iniciado"<< endl;
		setHome();
		
	}
	SDL_EnableKeyRepeat(1, 0);
 
	
	

	
}


kimbus::~kimbus()
{
 	//SDL_FreeSurface(screen);
 	SDL_FreeSurface(tree);
 	SDL_FreeSurface(grass);
 	SDL_FreeSurface(tallgrass);
	SDL_Quit();
}

void kimbus::updateScreen()
{
	SDL_Flip(screen);
}

void kimbus::addToScreen(SDL_Surface* surface, int x, int y, SDL_Rect *clip)
{
	
	dest.x=x;
	dest.y=y;
	SDL_BlitSurface(surface,clip,screen,&dest);

	
}


SDL_Surface* kimbus::getScreen()
{
	return screen;
}





bool kimbus::loadmap()
{
	int i=0;
	string temp;
	
	map_file.open("resources/map.txt");
	if (map_file)  // same as: if (map.good())
	{
		while (getline( map_file, temp ))  // same as: while (getline( map, line ).good())
		{
			map.push_back(temp);
		}
		map_file.close();
		for(i=0;i<map.size();i++)
		{
			cout << map.at(i) <<endl;
			
		}
		for(i=0;i<MAP_WIDTH;++i)
		{
			
			for(int j=0;j<MAP_HEIGHT;++j)
			{
				
				if(map.at(j).at(i)=='H')
				{
					pos.x=i;
					pos.y=j;
				}
			}
		}
		return true;
		
	}
	else
	{
		cout << "Fallo al abrir archivo de mapa" <<endl;
		return false;
		
	}
	
	return true;
	
}

void kimbus::drawmap()
{
	int i,j;


	
	for(i=0;i<MAP_WIDTH;++i)
	{

		for(j=0;j<MAP_HEIGHT;++j)
		{
			
 			char c=map.at(j).at(i);
// 			cout<< c <<endl;
			//draw map tiles
			
			
			switch(c)
			{
				case 'C':
					addToScreen(grass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					break;
					
					
				case 'A':
					addToScreen(grass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					addToScreen(tree,i*TILE_SIZE,j*TILE_SIZE,NULL);
					break;
					
				case 'T':
					addToScreen(grass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					addToScreen(tallgrass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					break;
					
				case 'H':
					addToScreen(grass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					addToScreen(home,i*TILE_SIZE,j*TILE_SIZE,NULL);
					break;
					
				case 'R':
					addToScreen(grass,i*TILE_SIZE,j*TILE_SIZE,NULL);
					addToScreen(rock,i*TILE_SIZE,j*TILE_SIZE,NULL);
					break;
			}
			
			
		}
	}
	//mapsurface=screen;
	
}



bool kimbus::loadTiles()
{
	grass= IMG_Load("resources/sprites/grass_tile.png");
	tree=IMG_Load("resources/sprites/tree_tile.png");
	tallgrass=IMG_Load("resources/sprites/tall_grass.png");
	textbox=IMG_Load("resources/sprites/textbox.png");
	home=IMG_Load("resources/sprites/home.png");
	rock=IMG_Load("resources/sprites/rock.png");
	if(!grass || !tree || !tallgrass || !textbox | !rock)
	{
		cout << "No se pudieron cargar algunos tiles. " <<SDL_GetError()<<endl;
		return false;
	}
	
	return true;
}


void kimbus::setHome()
{
	int i,j;
	
	
	
	for(i=0;i<MAP_WIDTH;++i)
	{
		
		for(j=0;j<MAP_HEIGHT;++j)
		{
			
			char c=map.at(j).at(i);
			// 			cout<< c <<endl;
			//draw map tiles
			
			
			if(c=='H')
			{
				pos.x=i;
				pos.y=j;
			}
			
			
		}
	}
	//mapsurface=screen;
	
}



void kimbus::mainloop()
{
	hero gold(MAP_WIDTH,MAP_HEIGHT);

	gold.setX((pos.x*TILE_SIZE));
	gold.setY((pos.y*TILE_SIZE));
	cout << pos.x<<endl;
	cout << pos.y<<endl;
	
	button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20),backbtn("resources/sprites/back.png",100,HEIGHT-(TILE_SIZE*3)+20);
	bool quit;
	Timer fps;
	string caption;
	int nLoop=0;
	int fast=false;
	bool pop_movement=false;
	
	while(!quit)
	{
		fps.start();
		
		
		if(pop_movement==true)
		{
			pop_movement=gold.animate_stack();
		}
		else
		{
			while( SDL_PollEvent( &event ) )
			{
				
				
				switch(event.type)
				{
					case SDL_QUIT:
						quit = true;
						break;
						
					case SDL_KEYDOWN:
						
						
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								quit=true;
								break;
								
								
							case SDLK_RETURN:
								fps.pause();
								break;
								
								
							case SDLK_SPACE:
								fast=true;
								break;
								
								
								
							case SDLK_k:
								if(pop_movement==false)
								pop_movement=gold.animate_stack();
							
								break;
								// 							case SDLK_UP:
								// 								
								// 								
								// 								break;
								// 								
								// 							case SDLK_DOWN:
								// 								
								// 								
								// 								break;
								// 								
								// 							case SDLK_LEFT:
								// 								
								// 								
								// 								break;
								// 								
								// 								
								// 							case SDLK_RIGHT:
								// 								
								// 								
								// 								break;
						}
						
						break;
						
							case SDL_KEYUP:
								if(event.key.keysym.sym==SDLK_SPACE)
									fast=false;
								break;
				}
				
				
				
				
				
				
				
				
			}
			gold.handle_events(map);
			
			if(homebtn.handleEvents(event)==CLICK)
			{
				
			}
			
			if(backbtn.handleEvents(event)==CLICK)
			{
				if(pop_movement==false)
					pop_movement=gold.animate_stack();
			}
			
		}

		drawmap();
		addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
		addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
		addToScreen(backbtn.getImage(),backbtn.getX(),backbtn.getY(),backbtn.getFrame());
		addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());
		//addToScreen(mapsurface,0,0,NULL);
		updateScreen();
		//cout <<fps.get_ticks()<<endl;
		
		if(fast==false)
		{
			if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
			{
				
				
				//SDL_WM_SetCaption(caption.c_str(),NULL);
				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
			}
		}
		
		else
		{
			if( fps.get_ticks() < 1000 / (FRAMES_PER_SECOND*4) )
			{
				
				SDL_Delay( ( 1000 / (FRAMES_PER_SECOND *4)) - fps.get_ticks() );
			}
		}
		//nLoop++;
		//cout <<nLoop <<endl;
		
		
		//SDL_Delay(100);
		
		
		
	}
	
	savemap();
	SDL_Quit();
	
}


void kimbus::initializeMap()
{
	int done=false;
	SDL_Rect selectedTile;
	SDL_Surface * selected;
	selected=IMG_Load("resources/sprites/outline.png");
	int click=false,tile=false;
	int mouse_x,mouse_y;
	SDL_Rect mouseTile;
	mouseTile.x=0;
	mouseTile.y=0;
	if(!selected)
	{
		cout << "No se pudo cargar recurso"<< SDL_GetError()<<endl;
		SDL_Quit();
		exit(1);
	}
	
	
	
	
	button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20);
	button treebtn("resources/sprites/treebtn.png",homebtn.getX()+homebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
	button grassbtn("resources/sprites/grassbtn.png",treebtn.getX()+treebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
	button tGrassbtn("resources/sprites/tallgrassbtn.png",grassbtn.getX()+grassbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
	button startbtn("resources/sprites/comenzar.png",tGrassbtn.getX()+tGrassbtn.getWidth()/2+100,HEIGHT-(TILE_SIZE*3)+20);
	button rockbtn("resources/sprites/rockbtn.png",20,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);
	while(!done)
	{
		drawmap();
		
		while( SDL_PollEvent( &event ) )
		{
			switch(event.type)
			{
				case SDL_QUIT:
					SDL_Quit();
					break;
					
				case SDL_MOUSEMOTION:
					mouse_x = event.motion.x; 
					mouse_y = event.motion.y;
					if(click==true)
					{
						if(( mouse_x > 0 ) && (mouse_x < WIDTH ) && ( mouse_y > 0 ) && ( mouse_y < HEIGHT-(TILE_SIZE*3) ))
						{
							
							mouseTile.x=mouse_x/TILE_SIZE;
							mouseTile.y=mouse_y/TILE_SIZE;
							mouseTile.x=mouseTile.x*TILE_SIZE;
							mouseTile.y=mouseTile.y*TILE_SIZE;
							
						}
					}
					
					
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					if( event.button.button == SDL_BUTTON_LEFT ) 
					{
						if(click==true)
						{
							if(( mouse_x > 0 ) && (mouse_x < WIDTH ) && ( mouse_y > 0 ) && ( mouse_y < HEIGHT-(TILE_SIZE*3) ))
							{
								mouse_x = event.button.x;
								mouse_y = event.button.y;
								mouseTile.x=mouse_x/TILE_SIZE;
								mouseTile.x*=TILE_SIZE;
								mouseTile.y=mouse_y/TILE_SIZE;
								mouseTile.y*=TILE_SIZE;
								setTile(click,tile,&mouseTile);
							}
						}
					}
					
					break;
			}
		}
		
		if(homebtn.handleEvents(event)==CLICK)
		{
			selectedTile.x=homebtn.getX();
			selectedTile.y=homebtn.getY();
			tile= HOME;
			click=true;
			
		}
		
		if(treebtn.handleEvents(event)==CLICK)
		{
			selectedTile.x=treebtn.getX();
			selectedTile.y=treebtn.getY();
			tile=TREE;
			click=true;
		}
		if(startbtn.handleEvents(event)==CLICK)
		{
			done=true;
		}
		if(grassbtn.handleEvents(event)==CLICK)
		{
			selectedTile.x=grassbtn.getX();
			selectedTile.y=grassbtn.getY();
			tile=GRASS;
			click=true;
		}
		if(tGrassbtn.handleEvents(event)==CLICK)
		{
			selectedTile.x=tGrassbtn.getX();
			selectedTile.y=tGrassbtn.getY();
			tile=TALL_GRASS;
			click=true;
		}
		if(rockbtn.handleEvents(event)==CLICK)
		{
			selectedTile.x=rockbtn.getX();
			selectedTile.y=rockbtn.getY();
			tile=ROCK;
			click=true;
		}
		addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
		addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
		addToScreen(treebtn.getImage(),treebtn.getX(),treebtn.getY(),treebtn.getFrame());
		addToScreen(grassbtn.getImage(),grassbtn.getX(),grassbtn.getY(),grassbtn.getFrame());
		addToScreen(tGrassbtn.getImage(),tGrassbtn.getX(),tGrassbtn.getY(),tGrassbtn.getFrame());
		addToScreen(startbtn.getImage(),startbtn.getX(),startbtn.getY(),startbtn.getFrame());
		addToScreen(rockbtn.getImage(),rockbtn.getX(),rockbtn.getY(),rockbtn.getFrame());
		if(click==true)
		{
			addToScreen(selected,selectedTile.x,selectedTile.y,NULL);
			addToScreen(selected,mouseTile.x,mouseTile.y,NULL);
		}
		
		
		
		updateScreen();
		SDL_Delay(50);
		//quit=true;
		
	}
}

void kimbus::setTile(int click, int tile,SDL_Rect * tilePos)
{
	int x,y;
	x=tilePos->x/TILE_SIZE;
	y=tilePos->y/TILE_SIZE;
	switch (tile)
	{
		case TREE:
			
			map.at(y).at(x)='A';
			break;
			
		case HOME:
			map.at(y).at(x)='H';
			map.at(pos.y).at(pos.x)='C';
			pos.x=x;
			pos.y=y;
			
			break;
			
		case GRASS:
			map.at(y).at(x)='C';
			break;
			
		case TALL_GRASS:
			map.at(y).at(x)='T';
			break;
			
		case ROCK:
			map.at(y).at(x)='R';
			break;
	}
}


posicion kimbus::getHome()
{
	return pos;
}



void kimbus::savemap()
{
	ofstream myfile ("resources/map.txt",ios::trunc);
	if (myfile.is_open())
	{/*
		myfile << "This is a line.\n";
		myfile << "This is anothers line.\n";
	*/
		for(int i=0;i<map.size();++i){
			myfile << map.at(i);
			myfile << "\n";
			
		}
		myfile.close();
	}
	
	else cout << "Unable to open file";

}




 