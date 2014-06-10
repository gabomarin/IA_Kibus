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
    mapsurface=SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH,HEIGHT,BPP ,
                                    0,0,0,0  );


    redAlpha = SDL_CreateRGBSurface(SDL_SWSURFACE, TILE_SIZE,TILE_SIZE,24 ,
                                    0,0,0,0  );
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



//	beedrill.create(MAP_WIDTH,MAP_HEIGHT);


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

void kimbus::addToMap(SDL_Surface* surface, int x, int y, SDL_Rect *clip)
{

    dest.x=x;
    dest.y=y;
    SDL_BlitSurface(surface,clip,mapsurface,&dest);


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

    case 4:
    default:
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
        for(i=0; i<map.size(); i++)
        {
            cout << map.at(i) <<endl;

        }
        for(i=0; i<MAP_WIDTH; ++i)
        {

            for(int j=0; j<MAP_HEIGHT; ++j)
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


    SDL_Rect alphaPos;

//     alphaPos.h= TILE_SIZE;
//     alphaPos.w=TILE_SIZE;
//     alphaPos.x=0;
//     alphaPos.y=0;
    //SDL_FillRect( redAlpha, &alphaPos,0xDD1110);
    //int alpha;
    for(i=0; i<MAP_HEIGHT; i++)
    {

        for(j=0; j<MAP_WIDTH; j++)
        {

            char c=map.at(i).at(j);
// 			cout<< c <<endl;
            //draw map tiles
            //alpha= heatMap[i][j];
            //cout << heatMap[i][j]<< " ";
            //SDL_SetAlpha(redAlpha,SDL_SRCALPHA,alpha);
            //SDL_SetAlpha(tallgrass,SDL_SRCALPHA,70);
            switch(c)
            {

            case 'C':
                addToMap(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);
                if(conexion[i][j].isVisitado())
                    addToMap(tallgrass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                //addToMap(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);

                break;


            case 'A':
                addToMap(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                addToMap(tree,j*TILE_SIZE,i*TILE_SIZE,NULL);


                //addToMap(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'T':
                addToMap(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToMap(tallgrass,j*TILE_SIZE,i*TILE_SIZE,NULL);
                //addToMap(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'H':
                addToMap(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);

                //addToMap(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                addToMap(home,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;

            case 'R':
                addToMap(grass,j*TILE_SIZE,i*TILE_SIZE,NULL);


                addToMap(rock,j*TILE_SIZE,i*TILE_SIZE,NULL);
                //addToMap(redAlpha,j*TILE_SIZE,i*TILE_SIZE,NULL);
                break;


            }
            //cout <<" " << alpha ;


        }

        //alpha-=20;
    }


    //mapsurface=screen;
    //SDL_FreeSurface(redAlpha);

}



bool kimbus::loadTiles()
{
    grass= IMG_Load("resources/sprites/grass_tile.png");
    tree=IMG_Load("resources/sprites/tree_tile.png");
    tallgrass=IMG_Load("resources/sprites/tall_grass.png");
    textbox=IMG_Load("resources/sprites/textbox.png");
    home=IMG_Load("resources/sprites/home.png");
    rock=IMG_Load("resources/sprites/rock.png");


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

void kimbus::recorrido_entrenado()
{
	
	int num_iteraciones=0;
    button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20),backbtn("resources/sprites/back.png",100,HEIGHT-(TILE_SIZE*3)+20);
    slider velocidad(120,20,20,600,1,40);
    bool quit=false;
    Timer fps;
    string caption;
    int kibus_resultado;
    int bee_resultado;


	

    
    gold.setHouse( pos.x, pos.y);
    //gold.bresenham(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT,pos.x,pos.y);
    gold.setLastPosition(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT);


    bool complete=false;



    int nLoop=1;
    int fast=false;
    bool pop_movement=false;


    resetMap();
    //drawmap();
    int i;
	move_kibus();
	gold.setX((posH.x*HERO_WIDTH));
	gold.setY((posH.y*HERO_HEIGHT));
    while(!quit)
    {
        fps.start();

        if(pop_movement==true)
        {
            //pop_movement=gold.animate_stack();
        }
        else
        {
            while( SDL_PollEvent( &event ) )
            {


                switch(event.type)
                {
                case SDL_QUIT:
                    exit(-11);
                    quit = true;
                    //return 0;
                    break;

                case SDL_KEYDOWN:


                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit=true;
                        exit(1);
                        break;


                    case SDLK_RETURN:
                        fps.pause();
                        break;


                    case SDLK_SPACE:
                        fast=true;
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

            //SDL_Rect temporal = gold.obtiene_celda_libre(map, conexion);
            //if(complete==false)
            //{
			primero_mejor(); 
			
			//cout <<camino.size()<<endl;
            //kibus_resultado=gold.handle_events(map,conexion);
            //}





           
            if(backbtn.handleEvents(event)==CLICK)
            {
                quit=true;
                //return 1;
            }

            int left_click=velocidad.handleEvents(event);
            switch(left_click)
            {
            case 0:
                break;

            case CLICK:
            case 2:
                //cout << "click en slider"<< endl;
                velocidad.calculateValue();
                break;

            }

        }
        if(gold.getFlag()==true )
        {
            drawmap();
            gold.setFlag(false);
        }

        drawmap();
        addToScreen(mapsurface,0,0,NULL);
        addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
        addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
        addToScreen(backbtn.getImage() , backbtn.getX(),backbtn.getY(),backbtn.getFrame());


        addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());


        if(gold.getX()== pos.x*TILE_SIZE && gold.getY()==pos.y*TILE_SIZE )
        {
            drawMessage(1);
            complete=true;
			quit=true;
            num_iteraciones++;
            //continue;

        }

        switch(kibus_resultado)
        {
            //SDL_Delay(1000);
        case -2:
            drawMessage(2);
            break;
            //quit=true;
        }
        //addToScreen(velocidad.updateSlider(), velocidad.getX(),velocidad.getY(),NULL);
        //addToScreen(mapsurface,0,0,NULL);
        updateScreen();
        //cout <<fps.get_ticks()<<endl;

        // 		if(fast==false)
        // 		{
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //SDL_WM_SetCaption(caption.c_str(),NULL);
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }




    }
}


SDL_Rect kimbus::primero_mejor()
{
	vector <SDL_Rect> camino;
	SDL_Rect temp;
	bool complete=false;
	int x,y;
	x= gold.getX()/HERO_WIDTH;
	y=gold.getY()/HERO_HEIGHT;
	int peso_actual;
	int mejor,i;
	mejor=-1;
	
	for(i=0;i<8;i++)
	{
		//cout << "peso  x"<<x<<" y"<<y<< " i"<<i<<" "<<conexion[y][x].arista[i].peso<<endl;
		
		if(conexion[y][x].arista[i].utilizado==false)
		{
			int tempx,tempy;
			tempx=conexion[y][x].arista[i].conectax;
			tempy=conexion[y][x].arista[i].conectay;
			if(tempx!=-1 && tempy!=-1)
			{
				
				if(map.at(tempy).at(tempx)!='A' && map.at(tempy).at(tempx)!='R')
				
				{
					if(mejor==-1)
						mejor=i;
					else if(conexion[y][x].arista[i].peso<conexion[y][x].arista[mejor].peso)
					{
						mejor=i;
					}	
				}
			}
		}		
	}
	
	if(conexion[y][x].arista[mejor].conectax==-1 && conexion[y][x].arista[mejor].conectay==-1)
	{
		
		int tempx=conexion[y][x].arista[mejor].conectax;
		int tempy=conexion[y][x].arista[mejor].conectay;
		conexion[y][x].arista[mejor].utilizado=true;
		
		gold.setX(movimientos.back().x*TILE_SIZE);
		gold.setY(movimientos.back().y*TILE_SIZE);
		movimientos.pop_back();
		
		
		//cout<< "entre"<<endl;
	}
	else
	{
		
			
		conexion[y][x].arista[mejor].utilizado=true;
		
		temp.x=conexion[y][x].arista[mejor].conectax;
		temp.y=conexion[y][x].arista[mejor].conectay;
		movimientos.push_back(temp);
		gold.setX(temp.x*TILE_SIZE);
		gold.setY(temp.y*TILE_SIZE);
		
	}
		

	
}



void kimbus::mainloop()
{

    int num_iteraciones=0;
    button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20),backbtn("resources/sprites/back.png",100,HEIGHT-(TILE_SIZE*3)+20);
    slider velocidad(120,20,20,600,1,40);
    bool quit;
    Timer fps;
    string caption;
    int kibus_resultado;
    int bee_resultado;
    gold.setX((posH.x*HERO_WIDTH));
    gold.setY((posH.y*HERO_HEIGHT));
    gold.setHouse( pos.x, pos.y);
    gold.setLastPosition(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT);
    conexion[posH.y][posH.x].setVisitado(true);
    maximo_historico=0;
    minimo_historico=0;
    int npasos;
    while(num_iteraciones<MAX_ITERACIONES)
    {
        cout <<"Iteracion #"<< num_iteraciones<<"/"<<MAX_ITERACIONES<<endl;
        npasos=0;
        gold.setX((posH.x*HERO_WIDTH));
        gold.setY((posH.y*HERO_HEIGHT));
        //gold.bresenham(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT,pos.x,pos.y);
        gold.setLastPosition(gold.getX()/HERO_WIDTH,gold.getY()/HERO_HEIGHT);
        bool complete=false;
        int nLoop=1;
        int fast=false;
        bool pop_movement=false;
        gold.clearRecorrido();
		conexion[gold.getY()/TILE_SIZE][gold.getX()/TILE_SIZE].setVisitado(true);


        resetMap();
        //drawmap();
        int i;

        while(!complete)
        {
            fps.start();

            if(pop_movement==true)
            {
                //pop_movement=gold.animate_stack();
            }
            else
            {
                while( SDL_PollEvent( &event ) )
                {


                    switch(event.type)
                    {
                    case SDL_QUIT:
                        exit(-11);
                        //quit = true;
                        //return 0;
                        break;

                    case SDL_KEYDOWN:


                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            //quit=true;
                            exit(1);
                            break;


                        case SDLK_RETURN:
                            fps.pause();
                            break;


                        case SDLK_SPACE:
                            fast=true;
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

                //SDL_Rect temporal = gold.obtiene_celda_libre(map, conexion);
                //if(complete==false)
                //{

                kibus_resultado=gold.handle_events(map,conexion);
                //}





                if(homebtn.handleEvents(event)==CLICK)
                {

                }

                if(backbtn.handleEvents(event)==CLICK)
                {
                    quit=true;
                    //return 1;
                }

                int left_click=velocidad.handleEvents(event);
                switch(left_click)
                {
                case 0:
                    break;

                case CLICK:
                case 2:
                    //cout << "click en slider"<< endl;
                    velocidad.calculateValue();
                    break;

                }

            }
            if(gold.getFlag()==true )
            {
                //drawmap();
                gold.setFlag(false);
            }

            //drawmap();
 			//addToScreen(mapsurface,0,0,NULL);
// 			addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
// 			addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
// 			addToScreen(backbtn.getImage() , backbtn.getX(),backbtn.getY(),backbtn.getFrame());


 			//addToScreen(gold.getSurface(), gold.getX(),gold.getY(),gold.getFrame());


            if(gold.getX()== pos.x*TILE_SIZE && gold.getY()==pos.y*TILE_SIZE )
            {
                //drawMessage(1);
                complete=true;
                num_iteraciones++;
                //continue;

            }

            switch(kibus_resultado)
            {
                //SDL_Delay(1000);
            case -2:
                //drawMessage(2);
                break;
                //quit=true;
            }
            //addToScreen(velocidad.updateSlider(), velocidad.getX(),velocidad.getY(),NULL);
            //addToScreen(mapsurface,0,0,NULL);
            //updateScreen();
            //cout <<fps.get_ticks()<<endl;

            // 		if(fast==false)
            // 		{
            if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            {


                //SDL_WM_SetCaption(caption.c_str(),NULL);
                //SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
            }
            // 		}
            //
            // 		else
            // 		{
            // 		int vel_multiplicacion= velocidad.getValue()/10+1;
            // 			if( fps.get_ticks() < 1500 / (FRAMES_PER_SECOND*vel_multiplicacion) )
            // 			{
            //
            // 				SDL_Delay( ( 1500 / (FRAMES_PER_SECOND *vel_multiplicacion)) - fps.get_ticks() );
            // 			}
            // 		//}

            // cout <<nLoop <<endl;


            //SDL_Delay(100);
            npasos++;


        }
        int conexiones=gold.conexiones.size();
		cout << conexiones<<endl<<endl;
        
        
        if(num_iteraciones==1)
        {
            maximo_historico=minimo_historico=conexiones;
        }
        else
        {
            if(conexiones>maximo_historico)
                maximo_historico=conexiones;

            if(conexiones<minimo_historico)
                minimo_historico=conexiones;
        }
        media_historica= (maximo_historico+minimo_historico)/2;


        //aplica bonus y castigos
        int modificador_peso= abs(media_historica-conexiones);
        int tipo;
        if(conexiones<=media_historica)
            tipo=PREMIO;
        else
            tipo=CASTIGO;
        altera_pesos(modificador_peso,tipo);
    }
    //savemap();


}

void kimbus::altera_pesos(int modificador_peso, int tipo)
{
    int i,j, posicion;
	
	struct arista temporal;
	
	while(!gold.conexiones.empty())
	{
		temporal=gold.conexiones.back();
		if(tipo==PREMIO)
		{
			conexion[temporal.nodo1.y][temporal.nodo1.x].arista[temporal.posicion].peso-=modificador_peso;
		}
		else
		{
			conexion[temporal.nodo1.y][temporal.nodo1.x].arista[temporal.posicion].peso+=modificador_peso;
		}
		gold.conexiones.pop_back();
	}	
}

void kimbus::move_kibus()
{

		
		selected=IMG_Load("resources/sprites/outline.png");
		
		mouseTile.x=0;
		mouseTile.y=0;
		if(!selected)
		{
			cout << "No se pudo cargar recurso"<< SDL_GetError()<<endl;
			SDL_Quit();
			exit(1);
		}
		
		int click=false,tile=false,left_click=false;
		int done=false;
		
		
		button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20);
		button treebtn("resources/sprites/treebtn.png",homebtn.getX()+homebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
		button grassbtn("resources/sprites/grassbtn.png",treebtn.getX()+treebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
		button tGrassbtn("resources/sprites/tallgrassbtn.png",grassbtn.getX()+grassbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
		
		button rockbtn("resources/sprites/rockbtn.png",20,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);
		button herobtn("resources/sprites/herobtn.png",rockbtn.getX()+rockbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);
		
		//slider de porcentaje, ancho,valor inicial, posicion X, posicion Y
		slider porcentaje(251,30,tGrassbtn.getX()+tGrassbtn.getWidth()/2+10,tGrassbtn.getY()+10,30,80);
		button randombtn("resources/sprites/randombtn.png", porcentaje.getX()+porcentaje.getRealWidth()+10,HEIGHT-(TILE_SIZE*3)+20);
		button clearbtn("resources/sprites/clearbtn.png",randombtn.getX()+randombtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
		button startbtn("resources/sprites/comenzar.png",randombtn.getX()+randombtn.getWidth(),HEIGHT-(TILE_SIZE*3)+20);
		
		button map_1("resources/sprites/1.png",tGrassbtn.getX()+tGrassbtn.getWidth()/2+20,tGrassbtn.getY()+35);
		button map_2("resources/sprites/2.png",map_1.getX()+map_1.getWidth()/2+10,tGrassbtn.getY()+35);
		button map_3("resources/sprites/3.png",map_2.getX()+map_2.getWidth()/2+10,tGrassbtn.getY()+35);
		button map_default("resources/sprites/4.png",map_3.getX()+map_3.getWidth()/2+10,tGrassbtn.getY()+35);
		
		
		//bresenham(posH.x,posH.y,pos.x,pos.y);
		//initialiceHeat();
		
		
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
									
									//                            initialiceHeat();
								}
							}
						}
						
						break;
				}
			}
			

			
			
			
			
			
			if(herobtn.handleEvents(event)==CLICK)
			{
				
				selectedTile.x=herobtn.getX();
				selectedTile.y=herobtn.getY();
				tile=HERO;
				click=true;
				//bresenham(posH.x,posH.y,pos.x,pos.y);
				
				
				
			}
			tile=HERO;
			
			
			if(startbtn.handleEvents(event)==CLICK)
			{
				done=true;
				//bresenham(posH.x,posH.y,pos.x,pos.y);
				//savemap();
			}
			
			
			
			
			
			addToScreen(mapsurface,0,0,NULL);
			addToScreen(textbox,0,HEIGHT-(TILE_SIZE*3),NULL);
			//addToScreen(homebtn.getImage(),homebtn.getX(),homebtn.getY(),homebtn.getFrame());
			
			addToScreen(startbtn.getImage(),startbtn.getX(),startbtn.getY(),startbtn.getFrame());
			
			addToScreen(herobtn.getImage(),herobtn.getX(),herobtn.getY(),herobtn.getFrame());
			
			
			addToScreen(gold.getSurface(),posH.x*TILE_SIZE,posH.y*TILE_SIZE,gold.getFrame());
			
			//SDL_FreeSurface(porcentaje_slider);
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
		SDL_FreeSurface(selected);
	
}

void kimbus::initializeMap()
{

    selected=IMG_Load("resources/sprites/outline.png");

    mouseTile.x=0;
    mouseTile.y=0;
    if(!selected)
    {
        cout << "No se pudo cargar recurso"<< SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    int click=false,tile=false,left_click=false;
    int done=false;


    button homebtn("resources/sprites/home.png",20,HEIGHT-(TILE_SIZE*3)+20);
    button treebtn("resources/sprites/treebtn.png",homebtn.getX()+homebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
    button grassbtn("resources/sprites/grassbtn.png",treebtn.getX()+treebtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
    button tGrassbtn("resources/sprites/tallgrassbtn.png",grassbtn.getX()+grassbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);

    button rockbtn("resources/sprites/rockbtn.png",20,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);
    button herobtn("resources/sprites/herobtn.png",rockbtn.getX()+rockbtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+TILE_SIZE+25);

    //slider de porcentaje, ancho,valor inicial, posicion X, posicion Y
    slider porcentaje(251,30,tGrassbtn.getX()+tGrassbtn.getWidth()/2+10,tGrassbtn.getY()+10,30,80);
    button randombtn("resources/sprites/randombtn.png", porcentaje.getX()+porcentaje.getRealWidth()+10,HEIGHT-(TILE_SIZE*3)+20);
    button clearbtn("resources/sprites/clearbtn.png",randombtn.getX()+randombtn.getWidth()/2,HEIGHT-(TILE_SIZE*3)+20);
    button startbtn("resources/sprites/comenzar.png",randombtn.getX()+randombtn.getWidth(),HEIGHT-(TILE_SIZE*3)+20);

    button map_1("resources/sprites/1.png",tGrassbtn.getX()+tGrassbtn.getWidth()/2+20,tGrassbtn.getY()+35);
    button map_2("resources/sprites/2.png",map_1.getX()+map_1.getWidth()/2+10,tGrassbtn.getY()+35);
    button map_3("resources/sprites/3.png",map_2.getX()+map_2.getWidth()/2+10,tGrassbtn.getY()+35);
    button map_default("resources/sprites/4.png",map_3.getX()+map_3.getWidth()/2+10,tGrassbtn.getY()+35);


    //bresenham(posH.x,posH.y,pos.x,pos.y);
    //initialiceHeat();


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
//                            initialiceHeat();
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
            //bresenham(posH.x,posH.y,pos.x,pos.y);
//            initialiceHeat();

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
            //bresenham(posH.x,posH.y,pos.x,pos.y);
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
//            initialiceHeat();
            SDL_Delay(250);
        }
        if(clearbtn.handleEvents(event)==CLICK)
        {
            clearmap();
//            initialiceHeat();
            SDL_Delay(250);
        }


        if(herobtn.handleEvents(event)==CLICK)
        {

            selectedTile.x=herobtn.getX();
            selectedTile.y=herobtn.getY();
            tile=HERO;
            click=true;
            //bresenham(posH.x,posH.y,pos.x,pos.y);



        }


        if(map_1.handleEvents(event)==CLICK)
        {
            loadmap(1);
//            initialiceHeat();
            drawmap();
        }

        if(map_2.handleEvents(event)==CLICK)
        {
            loadmap(2);
            //          initialiceHeat();
            drawmap();
        }

        if(map_3.handleEvents(event)==CLICK)
        {
            loadmap(3);
            //        initialiceHeat();
            drawmap();
        }

        if(map_default.handleEvents(event)==CLICK)
        {
            loadmap(4);
            //initialiceHeat();
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

        addToScreen(mapsurface,0,0,NULL);
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
        //SDL_FreeSurface(porcentaje_slider);
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
    SDL_FreeSurface(selected);
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

    string  mensaje;
    SDL_Color textColor;
    Uint32 boxcolor;

    messagebox = SDL_CreateRGBSurface(SDL_SWSURFACE, 400,80,24 ,
                                      screen->format->Rmask,screen->format->Gmask,screen->format->Bmask,
                                      screen->format->Amask  );

    font=TTF_OpenFont("resources/visitor1.ttf",18);


    textColor.b=255;
    textColor.g=255;
    textColor.r=255;





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
    position.x= 0;
    position.y= 0;
    position.w=400;
    position.h=80;

    SDL_FillRect(messagebox,&position, boxcolor);
    position.x= WIDTH/4;
    position.y= HEIGHT/3;

    addToScreen(messagebox,position.x,position.y,NULL);

    position.x=WIDTH/4+70;
    position.y=HEIGHT/3+30;
    addToScreen(texto,position.x,position.y,NULL);
    SDL_FreeSurface(texto);
    SDL_FreeSurface(messagebox);
    TTF_CloseFont(font);

    //SDL_FreeSurface(messagebox);
    //SDL_FreeSurface(texto);

}


void kimbus::resetMap()
{
    int i,j;
    for(i=0; i<MAP_HEIGHT; i++)
    {
        for(j=0; j<MAP_WIDTH; j++)
        {
            conexion[i][j].setVisitado(false);
			for(int posicion=0;posicion<8;posicion++)
				conexion[i][j].arista[posicion].utilizado=false;
			
        }
    }

}



