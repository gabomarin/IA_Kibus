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
#include <cstring>
using namespace std;
kimbus::kimbus()
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption( "Mundo de kimbus", NULL );
    SDL_WM_SetIcon(SDL_LoadBMP("resources/sprites/icon.bmp"),NULL);
    //cout <<SDL_GetError();
    char var[40];
    strcpy(var,"SDL_VIDEO_CENTERED=1");
    putenv(var);
    //Set up screen
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE );
    if(!screen)
    {
        cout << "Error al iniciar SDL. " << SDL_GetError()<< endl;
        exit(1);

    }

    else if(loadmap(4)==false)
    {
        exit(1);
    }

    else if(!loadTiles())
    {
        exit(1);
    }
    //Initialize SDL_ttf
    else if( TTF_Init() == -1 )
    {
        exit(1);

    }
    else
    {
        cout << "Mundo de Kimbus Iniciado"<< endl;
        setHome();
        srand(time(NULL));

    }
    SDL_EnableKeyRepeat(1, 0);
    gold.create( MAP_WIDTH,MAP_HEIGHT,pos.x,pos.y);
    cout << pos.x<<endl;
    cout <<pos.y<< endl;
    gold.setDirection(HERO_DOWN);
    bool valido=false;

// 	for(int i=0;i<5;i++)
// 		beedrill[i].create(MAP_WIDTH,MAP_HEIGHT);
	beedrill.create(MAP_WIDTH,MAP_HEIGHT);
	

    do
    {
        posH.y=rand()%(MAP_HEIGHT-1)+1;
        posH.x=rand()%(MAP_WIDTH-1)+1;
        //cout <<posH.x<<endl;
        //cout <<posH.y<<endl;
    } while(map.at(posH.y).at(posH.x)=='R'|| map.at(posH.y).at(posH.x)=='A');
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





bool kimbus::loadmap(int opc)
{
	int i=0;
	string temp;
	pos.x=0;
	pos.y=0;
	map.clear();
	switch(opc)
	{
		case 1:
			map_file.open("resources/intestino.txt");
			break;
			
		case 2:
			map_file.open("resources/muros.txt");
			
			break;
			
		case 3:
			
			map_file.open("resources/encierro.txt");
			break;
			
		case 4: default:
			map_file.open("resources/map.txt");
			break;
	}
	//map_file.open("resources/map.txt");
	if (map_file) // same as: if (map.good())
	{
		while (getline( map_file, temp )) // same as: while (getline( map, line ).good())
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

    SDL_Surface *redAlpha = SDL_CreateRGBSurface(SDL_SWSURFACE, TILE_SIZE,TILE_SIZE,24 ,
                            0,0,0,0  );
    SDL_Rect alphaPos;
    alphaPos.h= TILE_SIZE;
    alphaPos.w=TILE_SIZE;
    alphaPos.x=0;
    alphaPos.y=0;
    SDL_FillRect( redAlpha, &alphaPos,0xDD1110);
    int alpha;
    for(i=0; i<MAP_HEIGHT; i++)
    {

        for(j=0; j<MAP_WIDTH; j++)
        {

            char c=map.at(i).at(j);
// 			cout<< c <<endl;
            //draw map tiles
            alpha= heatMap[i][j];
            //cout << heatMap[i][j]<< " ";
            SDL_SetAlpha(redAlpha,SDL_SRCALPHA,alpha);
            //SDL_SetAlpha(tallgrass,SDL_SRCALPHA,70);
            switch(c)
            {

            case 'C':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);

                break;


            case 'A':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToScreen(tree,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'T':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToScreen(tallgrass,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'H':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(home,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'R':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToScreen(rock,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case '1':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToScreen(water1,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case '2':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToScreen(water2,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);


                break;

            case '3':
                addToScreen(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToScreen(water3,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToScreen(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);



                break;
            }
            //cout <<" " << alpha ;


        }

        //alpha-=20;
    }


    //mapsurface=screen;
    SDL_FreeSurface(redAlpha);

}



bool kimbus::loadTiles()
{
    grass= IMG_Load("resources/sprites/grass_tile.png");
    tree=IMG_Load("resources/sprites/tree_tile.png");
    tallgrass=IMG_Load("resources/sprites/tall_grass.png");
    textbox=IMG_Load("resources/sprites/textbox.png");
    home=IMG_Load("resources/sprites/home.png");
    rock=IMG_Load("resources/sprites/rock.png");
    water1=IMG_Load("resources/sprites/water1.png");
    water2=IMG_Load("resources/sprites/water2.png");
    water3=IMG_Load("resources/sprites/water3.png");
    if(!grass || !tree || !tallgrass || !textbox | !rock || !water1
            || !water2 || !water3	)
    {
        cout << "No se pudieron cargar algunos tiles. " <<SDL_GetError()<<endl;
        return false;
    }

    return true;
}


void kimbus::setHome()
{
    int i,j;



    for(i=0; i<MAP_HEIGHT; ++i)
    {

        for(j=0; j<MAP_WIDTH; ++j)
        {

            char c=map.at(i).at(j);
            // 			cout<< c <<endl;
            //draw map tiles


            if(c=='H')
            {
                pos.x=j;
                pos.y=i;
            }


        }
    }
    //mapsurface=screen;

}



void kimbus::mainloop()
{


    gold.setX((posH.x*TILE_SIZE));
    gold.setY((posH.y*TILE_SIZE));
	gold.setHouse( pos.x, pos.y);
	gold.bresenham(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT,pos.x,pos.y);
	gold.setLastPosition(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT);

// 	for(int i=0;i<5;i++)
// 	{
//     	beedrill[i].setX((posH.x)*TILE_SIZE);
//     	beedrill[i].setY( (posH.y)*TILE_SIZE);
// 		beedrill[i].setHouse(pos.x, pos.y);
//     	beedrill[i].bresenham(beedrill[i].getX()/HERO_WIDTH,beedrill[i].getY()/HERO_HEIGHT,pos.x,pos.y);
// 		beedrill[i].setLastPosition(beedrill[i].getX()/HERO_WIDTH,beedrill[i].getY()/HERO_HEIGHT);
// 	}
    
	beedrill.setX((posH.x)*TILE_SIZE);
		beedrill.setY( (posH.y)*TILE_SIZE);
		beedrill.setHouse(pos.x, pos.y);
		beedrill.bresenham(beedrill.getX()/HERO_WIDTH,beedrill.getY()/HERO_HEIGHT,pos.x,pos.y);
		beedrill.setLastPosition(beedrill.getX()/HERO_WIDTH,beedrill.getY()/HERO_HEIGHT);
    //cout << pos.x<<endl;
    //cout << pos.y<<endl;

    button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20),backbtn("resources/sprites/back.png",100,HEIGHT-(TILE_SIZE*3)+20);
    bool quit;
    Timer fps;
    string caption;
    int nLoop=0;
    int fast=false;
    bool pop_movement=false;
    int resultado;
	
	slider velocidad(120,20,20,600,1,40);

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

                    }

                    break;
                    //
                case SDL_KEYUP:
                    if(event.key.keysym.sym==SDLK_SPACE)
                        fast=false;
                    break;
                }

            }
            resultado=gold.handle_events(map);
			//for(int i=0;i<5;i++)
            //	beedrill[i].handle_events(map);
			//frames per animation * 5 rounds
			if(nLoop<40 && beedrill.is_returning()==false)
			{
				cout << "nloop " << nLoop<<endl;
				beedrill.handle_events(map);
			}
			else
			{
				
				beedrill.set_returning(true);
				if(beedrill.get_movement_stack_size()>0)
				{
					beedrill.animate_stack();
					nLoop=0;
					
				}
				else
				{
					beedrill.set_returning(false);
				}
				
				cout << beedrill.get_movement_stack_size()<<endl;
				
				
				
			}
            /*if(resultado==1) //se calcula de nuevo la linea
            {

            	while(resultado!=2)
            	{
            		resultado=gold.handle_events(map);
            		addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());
            		updateScreen();
            	}
            	bresenham(posH.x,posH.y,pos.x,pos.y);
            }
            if(resultado==2)
            {
            	while(resultado!=2)
            	{
            		resultado=gold.handle_events(map);
            		addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());
            		updateScreen();
            	}
            	bresenham(posH.x,posH.y,pos.x,pos.y);


            }*/

            if(homebtn.handleEvents(event)==CLICK)
            {

            }

            if(backbtn.handleEvents(event)==CLICK)
            {
                if(pop_movement==false)
                    pop_movement=gold.animate_stack();
            }
            
            int left_click=velocidad.handleEvents(event);
			switch(left_click)
			{
				case 0:
					break;
					
				case CLICK:  case 2:
					//cout << "click en slider"<< endl;
					velocidad.calculateValue();
					break;

			}

        }

        drawmap();
        addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
        addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
        addToScreen(backbtn.getImage() , backbtn.getX(),backbtn.getY(),backbtn.getFrame());
		
		
        addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());
		//for(int i=0;i<5;i++)
        //	addToScreen(beedrill[i].getSurface(), beedrill[i].getX(),beedrill[i].getY(),beedrill[i].getFrame());
		addToScreen(beedrill.getSurface(), beedrill.getX(),beedrill.getY(),beedrill.getFrame());

        //cout <<gold.getX()<<endl;
        //cout <<pos.x*TILE_SIZE<<endl;

        if(gold.getX()== pos.x*TILE_SIZE && gold.getY()==pos.y*TILE_SIZE )
        {
            drawMessage(1);
        }

        if(resultado==-2)
        {
            //SDL_Delay(1000);
            drawMessage(2);
            //quit=true;
        }
        addToScreen(velocidad.updateSlider(), velocidad.getX(),velocidad.getY(),NULL);
        //addToScreen(mapsurface,0,0,NULL);
        updateScreen();
        //cout <<fps.get_ticks()<<endl;

// 		if(fast==false)
// 		{
// 			if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
// 			{
// 
// 
// 				//SDL_WM_SetCaption(caption.c_str(),NULL);
// 				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
// 			}
// 		}
// 
// 		else
// 		{
		int vel_multiplicacion= velocidad.getValue()/10+1;
			if( fps.get_ticks() < 1500 / (FRAMES_PER_SECOND*vel_multiplicacion) )
			{

				SDL_Delay( ( 1500 / (FRAMES_PER_SECOND *vel_multiplicacion)) - fps.get_ticks() );
			}
		//}
        nLoop++;
        //cout <<nLoop <<endl;


        //SDL_Delay(100);



    }

    //savemap();
    SDL_Quit();

}


void kimbus::initializeMap()
{
    int done=false;
    SDL_Rect selectedTile;
    SDL_Surface * selected;
    selected=IMG_Load("resources/sprites/outline.png");
    int click=false,tile=false,left_click=false;
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

    button rockbtn("resources/sprites/rockbtn.png",20,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);
    button herobtn("resources/sprites/herobtn.png",rockbtn.getX()+rockbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);

    //slider de porcentaje, ancho,valor inicial, posicion X, posicion Y
    slider porcentaje(251,20,tGrassbtn.getX()+tGrassbtn.getWidth()/2+10,tGrassbtn.getY()+10,40,80);
    button randombtn("resources/sprites/randombtn.png", porcentaje.getX()+porcentaje.getRealWidth()+10,HEIGHT-(TILE_SIZE*3)+20);
    button clearbtn("resources/sprites/clearbtn.png",randombtn.getX()+randombtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
    button startbtn("resources/sprites/comenzar.png",randombtn.getX()+randombtn.getWidth(),HEIGHT-(TILE_SIZE*3)+20);

	button map_1("resources/sprites/1.png",tGrassbtn.getX()+tGrassbtn.getWidth()/2+20,tGrassbtn.getY()+35);
	button map_2("resources/sprites/2.png",map_1.getX()+map_1.getWidth()/2+10,tGrassbtn.getY()+35);
	button map_3("resources/sprites/3.png",map_2.getX()+map_2.getWidth()/2+10,tGrassbtn.getY()+35);
	button map_default("resources/sprites/4.png",map_3.getX()+map_3.getWidth()/2+10,tGrassbtn.getY()+35);


    bresenham(posH.x,posH.y,pos.x,pos.y);
    while(!done)
    {
        initialiceHeat();
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
            bresenham(posH.x,posH.y,pos.x,pos.y);

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
            bresenham(posH.x,posH.y,pos.x,pos.y);
            savemap();
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

        if(randombtn.handleEvents(event)==CLICK)
        {
            randomMap(porcentaje.getValue());
            SDL_Delay(250);
        }
        if(clearbtn.handleEvents(event)==CLICK)
        {
            clearmap();
            SDL_Delay(250);
        }


        if(herobtn.handleEvents(event)==CLICK)
        {

            selectedTile.x=herobtn.getX();
            selectedTile.y=herobtn.getY();
            tile=HERO;
            click=true;
            bresenham(posH.x,posH.y,pos.x,pos.y);



        }
        
        
        if(map_1.handleEvents(event)==CLICK)
		{
			loadmap(1);
			drawmap();
		}
		
		if(map_2.handleEvents(event)==CLICK)
		{
			loadmap(2);
			drawmap();
		}
		
		if(map_3.handleEvents(event)==CLICK)
		{
			loadmap(3);
			drawmap();
		}
		
		if(map_default.handleEvents(event)==CLICK)
		{
			loadmap(4);
			drawmap();
		}
		
		

        left_click=porcentaje.handleEvents(event);
        switch(left_click)
        {
        case 0:
            break;

        case CLICK:
            //cout << "click en slider"<< endl;
            porcentaje.calculateValue();
            break;

        case 2:
            //cout <<"click suelto slider" <<endl;
            porcentaje.calculateValue();
            //porcentaje.calculateValue();

            break;
        }


        addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
        addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
        addToScreen(treebtn.getImage(),treebtn.getX(),treebtn.getY(),treebtn.getFrame());
        addToScreen(grassbtn.getImage(),grassbtn.getX(),grassbtn.getY(),grassbtn.getFrame());
        addToScreen(tGrassbtn.getImage(),tGrassbtn.getX(),tGrassbtn.getY(),tGrassbtn.getFrame());
        addToScreen(randombtn.getImage(),randombtn.getX(),randombtn.getY(),randombtn.getFrame());
        addToScreen(startbtn.getImage(),startbtn.getX(),startbtn.getY(),startbtn.getFrame());
        addToScreen(rockbtn.getImage(),rockbtn.getX(),rockbtn.getY(),rockbtn.getFrame());
        addToScreen(herobtn.getImage(),herobtn.getX(),herobtn.getY(),herobtn.getFrame());
        addToScreen(clearbtn.getImage(),clearbtn.getX(),clearbtn.getY(),clearbtn.getFrame());

        addToScreen(gold.getSurface(),posH.x*TILE_SIZE,posH.y*TILE_SIZE,gold.getFrame());
		
		addToScreen(map_1.getImage(),map_1.getX(),map_1.getY(),map_1.getFrame() );
		addToScreen(map_2.getImage(),map_2.getX(),map_2.getY(),map_2.getFrame() );
		addToScreen(map_3.getImage(),map_3.getX(),map_3.getY(),map_3.getFrame() );
		addToScreen(map_default.getImage(),map_default.getX(),map_default.getY(),map_default.getFrame() );

        addToScreen(porcentaje.updateSlider(),porcentaje.getX(),porcentaje.getY(),NULL);
        //porcentaje.setValue(porcentaje.getValue()+1);
        //porcentaje.calculateValue();



        //porcentaje.setValue(porcentaje.getValue()+1);
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
    if(x==0 ||x==MAP_WIDTH-1 ||y==0 ||y==MAP_HEIGHT-1)
    {
        cout << "las orillas no se pueden quitar"<<endl;
    }
    else
    {
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

        case HERO:
            if(map.at(y).at(x)!='R'&& map.at(y).at(x)!='A') {

                posH.x=x;
                posH.y=y;
            }
            break;
        }
    }

}


posicion kimbus::getHome()
{
    return pos;
}



void kimbus::savemap()
{
    ofstream myfile ("resources/map.txt",ios::trunc),heat("resources/map_heat.txt", ios::trunc);


    //borramos los banderines
    for(int i=0; i<MAP_HEIGHT; ++i)
    {

        for(int j=0; j<MAP_WIDTH; ++j)
        {

            if(map.at(i).at(j)=='1' || map.at(i).at(j)=='2'  || map.at(i).at(j)=='3')
            {
                map.at(i).at(j)=='C';
            }
        }
    }


    if (myfile.is_open())
    {   /*
        myfile << "This is a line.\n";
        myfile << "This is anothers line.\n";
        */
        for(int i=0; i<map.size(); ++i) {
            myfile << map.at(i);
            myfile << "\n";

        }
        myfile.close();
    }

    else cout << "Unable to open file";



    if (heat.is_open())
    {   /*
        myfile << "This is a line.\n";
        myfile << "This is anothers line.\n";
        */




        for(int i=0; i<MAP_HEIGHT; i++)
        {
            for(int j=0; j<MAP_WIDTH; j++)
            {

                heat <<heatMap[i][j] << " ";
                //cout <<"j " << j;

            }
            heat<<endl;


        }
        
//         for(int i=0; i<MAP_HEIGHT; i++)
// 		{
// 			for(int j=0; j<MAP_WIDTH; j++)
// 			{
// 				//heatMap[i][j]=alpha;
// 				cout <<"i["<<i<<"]"<<" j["<<j<<"]"<<heatMap[i][j] << endl;
// 				//cout <<"j " << j;
// 				
// 			}
// 			//alpha-=12;
// 			
// 			
// 			
// 			//cout << endl;
// 		}
		//SDL_Delay(2000);
		//cout << endl;
        myfile.close();
        cout <<" mapa guardado";

    }

}




void kimbus::randomMap(int value)
{
    int i,j,total=0,cantidad;
    total=MAP_WIDTH*MAP_HEIGHT;
    int random;
    int x1,y1;
	//cout << total;
    cantidad= (total*value)/100;
    cantidad-= (MAP_HEIGHT*2-MAP_WIDTH*2);
    for(i=0; i<MAP_WIDTH; ++i)
    {
        for(j=0; j<MAP_HEIGHT; ++j)
        {
            map.at(j).at(i)='C';
        }
    }
    //c t a r

    i=0;
    while(i<cantidad)
    {
        do
        {
            y1=rand()%MAP_HEIGHT;
            x1=rand()%MAP_WIDTH;

        } while(map.at(y1).at(x1)=='R'|| map.at(y1).at(x1)=='A');

        random=rand()%21;
        if(random<10)
        {
            map.at(y1).at(x1)='A';
            i++;
        }
        else if(random >=10 && random <17)
        {
            map.at(y1).at(x1)='T';
            //No se considera obstaculo
        }
        else
        {
            map.at(y1).at(x1)='R';
            i++;
        }

        //map[x1][y1]=157;

    }

    y1=rand()%(MAP_HEIGHT-2)+1;
    x1=rand()%(MAP_WIDTH-2)+1;
    map.at(y1).at(x1)='H';

    pos.x=x1;
    pos.y=y1;
    do
    {

        y1=rand()%(MAP_HEIGHT-2)+1;
        x1=rand()%(MAP_WIDTH-2)+1;

    } while(map.at(y1).at(x1)=='R'|| map.at(y1).at(x1)=='A' 	);
    posH.x=x1;
    posH.y=y1;

    for(i=0; i<MAP_WIDTH; ++i)
    {
        map.at(0).at(i)='A';
        map.at(MAP_HEIGHT-1).at(i)='A';
    }
    for(i=0; i<MAP_HEIGHT; ++i)
    {
        map.at(i).at(0)='A';
        map.at(i).at(MAP_WIDTH-1)='A';
    }

    //getHome();
}


void kimbus:: bresenham(int x1, int y1, int x2, int y2)
{
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    gold.dropList();

    addToScreen(gold.getSurface(),x1*TILE_SIZE,y1*TILE_SIZE,gold.getFrame());

    gold.pushLine(x1,y1);

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            addToScreen(gold.getSurface(),x1*TILE_SIZE,y1*TILE_SIZE,gold.getFrame());
            gold.pushLine(x1,y1);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            //plot(x1, y1);
            addToScreen(gold.getSurface(),x1*TILE_SIZE,y1*TILE_SIZE,gold.getFrame());
            gold.pushLine(x1,y1);
        }
    }
    //for(int i=0;i<gold.)
    //gold.printList();
    gold.popLine();
    //cout <<"Despues "<<endl;
    //gold.printList();
}


void kimbus:: clearmap()
{
    int i;
    for( i=0; i<MAP_WIDTH; ++i)
    {
        for(int j=0; j<MAP_HEIGHT; ++j)
        {
            map.at(j).at(i)='C';
        }
    }
    pos.y=rand()%(MAP_HEIGHT-2)+1;
    pos.x=rand()%(MAP_WIDTH-2)+1;
    map.at(pos.y).at(pos.x)='H';

    posH.y=rand()%(MAP_HEIGHT-2)+1;
    posH.x=rand()%(MAP_WIDTH-2)+1;

    for(i=0; i<MAP_WIDTH; ++i)
    {
        map.at(0).at(i)='A';
        map.at(MAP_HEIGHT-1).at(i)='A';
    }
    for(i=0; i<MAP_HEIGHT; ++i)
    {
        map.at(i).at(0)='A';
        map.at(i).at(MAP_WIDTH-1)='A';
    }


}



void kimbus::drawMessage(int tipo)
{
    SDL_Surface *texto;
    TTF_Font *font;
    SDL_Rect posicion;
    string  mensaje;
    SDL_Color textColor;
    Uint32 boxcolor;
    textColor.b=255;
    textColor.g=255;
    textColor.r=255;
    SDL_Surface *messagebox = SDL_CreateRGBSurface(SDL_SWSURFACE, 400,80,24 ,
                              screen->format->Rmask,screen->format->Gmask,screen->format->Bmask,
                              screen->format->Amask  );

    font=TTF_OpenFont("resources/visitor1.ttf",18);

    if( tipo==1 )
    {
        mensaje= "Kibus llego al destino!! :D ";
        texto = TTF_RenderText_Solid( font, mensaje.c_str(), textColor );
        boxcolor= 0x151EC5;
    }

    else if( tipo==2 )
    {
        mensaje= "Kibus se atoro :(";
        texto = TTF_RenderText_Solid( font, mensaje.c_str(), textColor );
        boxcolor= 0x852D0F;
    }

    else
    {
        mensaje = "algo ocurrio";
        texto = TTF_RenderText_Solid( font, mensaje.c_str(), textColor );
        boxcolor= 0x854D23;
    }
    posicion.x= 0;
    posicion.y= 0;
    posicion.w=400;
    posicion.h=80;

    SDL_FillRect(messagebox,&posicion, boxcolor);
    posicion.x= WIDTH/4;
    posicion.y= HEIGHT/3;

    addToScreen(messagebox,posicion.x,posicion.y,NULL);

    posicion.x=WIDTH/4+70;
    posicion.y=HEIGHT/3+30;
    addToScreen(texto,posicion.x,posicion.y,NULL);




}


void kimbus::initialiceHeat()
{
    int x,y;
    int alpha;
    for(y=0; y<MAP_HEIGHT; y++)
    {
        for(x=0; x<MAP_WIDTH; x++)
        {
			alpha = MAX_HEAT - ( sqrt( pow( x - pos.x , 2 ) + pow( y - pos.y , 2 ) ) * 10 );
			if(alpha<0)
				alpha=0;
            heatMap[y][x]=alpha;
		 	//cout <<heatMap[i][j] << " ,";
            //cout <<"j " << j;

        }
       



		//cout << endl;
    }
   
    
}
