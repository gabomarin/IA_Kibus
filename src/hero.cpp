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

hero::hero(int map_width, int map_height)
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
    x_=5;
    y_=(HERO_HEIGHT-HERO_WIDTH)*-1;
    animation=false;
    this->map_height= map_height;
    this->map_width=map_width;



}

hero::hero()
{

}


void hero::create(int map_width, int map_height,int posx, int posy)
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
    destx=posx;
    desty=posy;


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
    if(direction==UP_RIGHT || direction== DOWN_RIGHT)
    {
        return &frame[animation_frame][HERO_RIGHT];
    }
    else if(direction==UP_LEFT || direction== DOWN_LEFT)
    {
        return &frame[animation_frame][HERO_LEFT];
    }
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

int hero:: handle_events(vector <string> &map) // si regresa true se calcula la linea de nuevo
{

    //If a key was pressed
    int resultado=false;
    bool ciclo=false;
    int cont=0;
    int movement;
    //SDL_Rect
    if(line_stack.size()>0) {


//         else {
//             cout << "Que jodidos paso!!"<<endl;
//         }


        if(status==STAND)
        {
            movement=calculateDirection();
            //printList();

            while(ciclo==false)
            {
                int cont_rep=0;  //contara cuantas veces cae en el random la misma posicion,

                if(cont==30)
                {
                    //cout<< "D:"<<endl;
                    //printList();
                    popLine();
                    movement=calculateDirection();
                    
                }
                else if(cont>=60)
                {
					
                    return -2;
                }
                if(cont<60)
                    cont+=1;
                //cout << cont <<endl;


                switch(movement)
                {
                case HERO_UP:
                    cout << "arriba"<<endl;

                    if(y_/HERO_HEIGHT>0)
                    {
                        cout << map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))<<endl;
                        if((map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))=='A')
                                || (map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))=='R')||
                                (map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_UP)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
 								setBanderin(map,lastp);	
							}
	
                            resultado=true;
                            obstaculo=1;
							//continue;
                            
                        }
                        else 
						{
							
							direction=HERO_UP;
							status=MOVEMENT;
							current_frame=0;
							animation_frame=0;
							// 							movement_stack.push_back(HERO_UP);
							// 							cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=HERO_DOWN;
							//line_stack.erase(line_stack.begin());
							printList();
							ciclo=true;
							
							//ciclo=true;
						}


                    }
                    
                    /*else if(y_/HERO_HEIGHT<0)
                    {
                    	do
                    	{
                    		movement=rand()%8;

                    		if(movement!=HERO_UP)
                    		{
                    			cont_rep=8;
                    		}
                    		cont_rep++;
                    	} while(cont_rep<8);

                    	resultado=true;
                    	obstaculo=1;
                    	continue;
                    }
                    	*/
                    

                    break;

                case HERO_DOWN:
                    cout << "abajo"<<endl;
                    if(y_/HERO_WIDTH<map_height-1)
                        if((map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH))=='A'
                                ||(map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH))=='R' ||
                                (map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH)=='3'))
                        {

                            //no hacer nada

                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_DOWN)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}

                            //movement=DOWN_LEFT;
                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else if(y_/HERO_WIDTH>map_height-2)
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_DOWN)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=HERO_DOWN;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
// 							movement_stack.push_back(HERO_DOWN);
// 							cout <<movement_stack.size()<<endl;
                            lastPosition.x=x_/HERO_WIDTH;
                            lastPosition.y=y_/HERO_HEIGHT;
							lastp=HERO_UP;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }
                    break;

                case HERO_LEFT:
                    cout << "izquierda"<<endl;
                    if(x_/HERO_WIDTH>0)
                        if((map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)-1)=='A')
                                ||(map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)-1)=='R')||
                                (map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)-1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH<=0)
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=HERO_LEFT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
// 							movement_stack.push_back(HERO_LEFT);
// 							cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=HERO_RIGHT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }
                    break;


                case HERO_RIGHT:
                    cout << "derecha"<<endl;
                    if(x_/HERO_WIDTH<map_width-1)
                        if((map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)+1))=='A'
                                || (map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)+1))=='R'||
                                (map.at(y_/HERO_HEIGHT).at((x_/HERO_WIDTH)+1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH>map_width-2  )
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=HERO_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}
                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=HERO_RIGHT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
                            //movement_stack.push_back(HERO_RIGHT);
                            //cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=HERO_LEFT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }
                    break;

                case UP_RIGHT:
                    cout << "arriba derecha"<<endl;
                    if(x_/HERO_WIDTH<map_width-1 && y_/HERO_HEIGHT>0)
                        if((map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)+1))=='A'
                                || (map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)+1))=='R'||
                                (map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)+1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=UP_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}
							
                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH>map_width-2 || y_/HERO_HEIGHT<=0)
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=UP_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=UP_RIGHT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
                            //movement_stack.push_back(HERO_RIGHT);
                            //cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=DOWN_LEFT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }


                    break;

                case DOWN_RIGHT:
                    cout << "abajo derecha"<<endl;
                    if(x_/HERO_WIDTH<map_width-1 && y_/HERO_WIDTH<map_height-1)
                        if((map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)+1))=='A'
                                || (map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)+1))=='R'||
                                (map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)+1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=DOWN_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}
                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH>map_width-2 || y_/HERO_WIDTH>map_height-2)
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=DOWN_RIGHT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=DOWN_RIGHT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
                            //movement_stack.push_back(HERO_RIGHT);
                            //cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=UP_LEFT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }


                    break;


                case UP_LEFT:
                    cout << "arriba izquierda"<<endl;
                    if(x_/HERO_WIDTH>0 && y_/HERO_HEIGHT>0)
                        if((map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)-1)=='A')
                                ||(map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)-1)=='R')||
                                (map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH)-1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=UP_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}
                            obstaculo=1;
                            resultado=true;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH<=0 || y_/HERO_HEIGHT<=0)
                        {
                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=UP_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=UP_LEFT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
                            // 							movement_stack.push_back(HERO_LEFT);
                            // 							cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=DOWN_RIGHT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }

                    break;

                case DOWN_LEFT:
                    cout << "abajo izquierda"<<endl;
                    if(y_/HERO_WIDTH<map_height-1 &&x_/HERO_WIDTH>0)
                        if((map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)-1)=='A')
                                ||(map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)-1)=='R')||
                                (map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)-1)=='3'))
                        {

                            //no hacer nada
                            do
                            {
                                movement=rand()%8;

                                if(movement!=DOWN_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);
							if(movement==lastp)
							{
								setBanderin(map,lastp);	
							}
                            obstaculo=1;
                            resultado=true;
                            //continue;
                        }
                        else if(x_/HERO_WIDTH<=0 || y_/HERO_WIDTH>map_height-2)
                        {
                            do
                            {
                                movement=rand()%8;

                                if(movement!=DOWN_LEFT)
                                {
                                    cont_rep=8;
                                }
                                cont_rep++;
                            } while(cont_rep<8);

                            resultado=true;
                            obstaculo=1;
                            //continue;
                        }
                        else
                        {

                            direction=DOWN_LEFT;
                            status=MOVEMENT;
                            current_frame=0;
                            animation_frame=0;
                            // 							movement_stack.push_back(HERO_LEFT);
                            // 							cout <<movement_stack.size()<<endl;
							lastPosition.x=x_/HERO_WIDTH;
							lastPosition.y=y_/HERO_HEIGHT;
							lastp=UP_RIGHT;
                            //line_stack.erase(line_stack.begin());
                            printList();
                            ciclo=true;
                        }


                    break;

                case 8://caso extraño que no deberia de llegar aqui, pero sucede y es la unica fora de arreglarlo
                    //cout <<"Algo paso"<<endl;
                    //popLine();

                    bresenham(x_/HERO_WIDTH,y_/HERO_HEIGHT,destx,desty);
                    movement=calculateDirection();
                    //movement=calculateDirection();
                    break;
                }
            }

        }

        if(status==MOVEMENT		)
        {
            //status=STAND;
            //animation_frame=1;
            //int movement=0;
            
                switch(direction)
                {
                case HERO_DOWN:
                    y_ += HERO_HEIGHT/8;
                    break;

                case HERO_UP:
                    y_ -= HERO_HEIGHT/8 ;
                    break;

                case HERO_LEFT:
                    x_ -= HERO_WIDTH/8 ;
                    break;

                case HERO_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    break;

                case UP_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    y_ -= HERO_HEIGHT/8 ;
                    break;

                case DOWN_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    y_ += HERO_HEIGHT/8 ;
                    break;

                case UP_LEFT:
                    x_ -= HERO_WIDTH/8 ;
                    y_ -= HERO_HEIGHT/8;
                    break;

                case DOWN_LEFT:
                    x_ -= HERO_WIDTH/8 ;
                    y_ += HERO_HEIGHT/8;
                    break;
                }
               
				if(current_frame<=7)
				{
					switch(current_frame)
					{
						case 0:
						case 4:
							animation_frame=2;
							break;
							
						case 1 :
						case 5:
							animation_frame=1;
							break;
							
						case 2:
						case 6:
							animation_frame=0;
							break;
							
						case 3:
							animation_frame=1;
							break;
						case 7:
							animation_frame=1;
							//movement=16;
							status=STAND;
							
							if(obstaculo==1)
							{
								//cout << "x sss "<<destx<<" y "<<desty;
								//SDL_Delay(2000);
// 								bresenham(x_/HERO_WIDTH,y_/HERO_HEIGHT,destx,desty);
// 								if(line_stack.at(0).x==lastPosition.x &&
// 									line_stack.at(0).y==lastPosition.y)
// 								{
// 									if(map.at(lastPosition.y).at(lastPosition.x)=='C' || map.at(y_/HERO_HEIGHT).at(lastPosition.x)=='T')
// 									{
// 										map.at(lastPosition.y).at(lastPosition.x)='1';
// 									}
// 									else if(map.at(lastPosition.y).at(lastPosition.x)=='1')
// 									{
// 										map.at(lastPosition.y).at(lastPosition.x)='2';
// 									}
// 									else if(map.at(lastPosition.y).at(lastPosition.x)=='2')
// 									{
// 										map.at(lastPosition.y).at(lastPosition.x)='3';
// 									}
// 									
// 									printMap(map);
// 								}
								obstaculo=0;
								
								
								printList();
								
							}
							else
								line_stack.erase(line_stack.begin());
							break;
							
					}
					current_frame++;
            }




        }
    }
    else
    {
        //para completar animacion cuando se vacia la pila
        if(status==MOVEMENT		)
        {
            //status=STAND;
            //animation_frame=1;
            int movement=0;
            if(current_frame<=7)
            {
                switch(current_frame)
                {
                case 0:
                case 4:
                    animation_frame=2;
                    break;

                case 1 :
                case 5:
                    animation_frame=1;
                    break;

                case 2:
                case 6:
                    animation_frame=0;
                    break;

                case 3:
                    animation_frame=1;
                    break;
                case 7:
                    animation_frame=1;
                    //movement=16;
                    status=STAND;
					line_stack.erase(line_stack.begin());
                    break;
                }
                switch(direction)
                {
                case HERO_DOWN:
                    y_ += HERO_HEIGHT/8;
                    break;

                case HERO_UP:
                    y_ -= HERO_HEIGHT/8 ;
                    break;

                case HERO_LEFT:
                    x_ -= HERO_WIDTH/8;
                    break;

                case HERO_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    break;

                case UP_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    y_ -= HERO_HEIGHT/8 ;
                    break;

                case DOWN_RIGHT:
                    x_ += HERO_WIDTH/8 ;
                    y_ += HERO_HEIGHT/8 ;
                    break;

                case UP_LEFT:
                    x_ -= HERO_WIDTH/8 ;
                    y_ -= HERO_HEIGHT/8 ;
                    break;

                case DOWN_LEFT:
                    x_ -= HERO_WIDTH/8 ;
                    y_ += HERO_HEIGHT/8 ;
                    break;
                }
                current_frame++;
            }




        }
    }
    return resultado;
}


bool hero::checkColision(vector <string> map)
{

    //no utilizado
    return false;
}





bool hero::animate_stack()
{

    if(movement_stack.size()==0)
        return false;

    cout <<movement_stack.size()<<endl;
    cout << movement_stack.back() << endl;
    if(status==STAND)
    {

        switch( movement_stack.back() )
        {
        case HERO_RIGHT:

            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=HERO_LEFT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=0;

            break;
        case HERO_LEFT:


            direction=HERO_RIGHT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=0;

            break;

        case HERO_UP:


            direction=HERO_DOWN;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=0;


            break;

        case HERO_DOWN:


            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=HERO_UP;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=0;


            break;

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
            case 0:
            case 4:
                animation_frame=2;
                break;

            case 1 :
            case 5:
                animation_frame=1;
                break;

            case 2:
            case 6:
                animation_frame=0;
                break;

            case 3:
                animation_frame=1;
                break;
            case 7:
                animation_frame=1;
                //movement=16;
                status=STAND;
                movement_stack.pop_back();
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


void hero::pushLine(int x, int y)
{
    SDL_Rect temp;
    temp.x=x;
    temp.y=y;
    line_stack.push_back(temp);
}

void hero:: insertFirst(int x, int y)
{
    SDL_Rect temp;
    temp.x=x;
    temp.y=y;
    line_stack.insert(line_stack.begin(),temp);
}


int hero::getLineX()
{
    SDL_Rect temp;

    temp=line_stack.front();
    return temp.x;

}




int hero::getLineY()
{
    SDL_Rect temp;

    temp=line_stack.front();
    return temp.y;

}

SDL_Rect hero::popLine()
{
    line_stack.erase(line_stack.begin());
}

void hero::show()
{

}


void hero::printList()
{
    //cout << line_stack.size();
    for(int i=0; i<line_stack.size(); i++)
    {
        cout << "X = "<<line_stack.at(i).x<< "      Y = "<< line_stack.at(i).y<<endl;

    }
    cout <<endl<<endl;

}


void hero::dropList()
{
    line_stack.clear();
}


int hero::calculateDirection()
{
    int movement;
	SDL_Rect hero;
    SDL_Rect temp;
    temp= line_stack.front();
    int tempx, tempy;
	

	hero.x=x_/HERO_WIDTH;
	hero.y=y_/HERO_HEIGHT;
    //verifica que tipo de movimiento tendra que hacer
	tempx=hero.x-temp.x;
	tempy=hero.y-temp.y;
	
    //cout << "tempx "<<tempx<< endl;
    //cout <<"temp.x "<<temp.x<<endl;
    //cout << "tempy"<<tempy<<endl;


    //verifica en que direccion debe de ir
    if(tempx==-1&&tempy==1)
    {
        //tomaria diagonal derecha hacia arriba
        movement=UP_RIGHT;
    }
    else if(tempx==-1 &&tempy==0)
    {
        movement=HERO_RIGHT;


    }
    else if(tempx==-1 && tempy==-1)
    {
        movement=DOWN_RIGHT;
    }

    else if(tempx==0 && tempy==-1)
    {
        movement=HERO_DOWN;
    }

    else if(tempx==1 && tempy==-1)
    {
        movement=DOWN_LEFT;
    }

    else if(tempx==1 && tempy==0)
    {
        movement=HERO_LEFT;
    }

    else if(tempx==1 && tempy==1)
    {
        movement=UP_LEFT;
    }

    else if(tempx==0 && tempy==1)
    {
        movement=HERO_UP;
    }
    else
	{
		movement=8;
	}
    return movement;
}

void hero:: bresenham(int x1, int y1, int x2, int y2)
{
    int delta_x(x2 - x1);
    //cout <<"x1= "<<x1<<" y1"<<y1 <<" x2="<<x2<<" y2="<<y2<<endl;
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    dropList();

    //addToScreen(gold.getSurface(),x1*48,y1*48,gold.getFrame());

    pushLine(x1,y1);

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

            //addToScreen(gold.getSurface(),x1*48,y1*48,gold.getFrame());
            pushLine(x1,y1);
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
            //addToScreen(gold.getSurface(),x1*48,y1*48,gold.getFrame());
            pushLine(x1,y1);
        }
    }
    //for(int i=0;i<gold.)
    printList();
    popLine();
    cout <<"Despues "<<endl;
    printList();
}

void hero::printMap(vector <string > map)
{
    for(int i=0; i<map.size(); i++)
    {
        cout <<map.at(i)<<endl;
    }
}


void hero::setHouse(int posx, int posy)
{
    destx=posx;
    desty=posy;
}


void hero::setLastPosition(int x, int y)
{
	lastPosition.x=x;
	lastPosition.y=y;
}


void hero::setBanderin(vector <string> &map, int posicion)
{
	int x=0,y=0;
	switch(posicion)
	{
		case HERO_UP:
			y=1;
			
			break;
			
		case HERO_DOWN:
			y=-1;
			break;
			
		case HERO_LEFT:
			x=1;
			break;
			
		case HERO_RIGHT:
			x=-1;
			break;
			
		case UP_LEFT:
			y=1;
			x=1;
			break;
			
		case UP_RIGHT:
			y=1;
			x=-1;
			break;
			
		case DOWN_LEFT:
			x=1;
			y=-1;
			break;
			
		case DOWN_RIGHT:
			x=-1;
			y=-1;
			break;
	}
	if(map.at(lastPosition.y+y).at(lastPosition.x+x)=='C' || map.at(lastPosition.y+y).at(lastPosition.x+x)=='T')
	{
		map.at(lastPosition.y+y).at(lastPosition.x+x)='1';
	}
	else if(map.at(lastPosition.y+y).at(lastPosition.x+x)=='1')
	{
		map.at(lastPosition.y+y).at(lastPosition.x+x)='2';
	}
	else if(map.at(lastPosition.y+y).at(lastPosition.x+x)=='2')
	{
		map.at(lastPosition.y+y).at(lastPosition.x+x)='3';
	}
	
	
}

