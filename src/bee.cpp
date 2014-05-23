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
    cont=0;

}

void bee::create(int map_width, int map_height)
{
    file= "resources/sprites/bee.png";
    sprite= IMG_Load(file.c_str());
    if(!sprite)
    {
        cout << "Error con gold " << SDL_GetError()<< endl;
        exit(1);
    }

    cout << "Beedrill cargado exitosamente" <<endl;



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
    cont=0;
    returning=false;
    line_stack.clear();
    movement_stack.clear();
}

int bee:: handle_events(vector <string> &map) // si regresa true se calcula la linea de nuevo
{

    //If a key was pressed
    int resultado=false;
    bool ciclo=false;
    int cont=0;
    int movement;
    //SDL_Rect


    if(status==STAND)
    {
        movement=rand()%8;
        //printList();

        while(ciclo==false)
        {
            int cont_rep=0;  //contara cuantas veces cae en el random la misma posicion,

            if(cont==30)
            {
                //cout<< "D:"<<endl;
                //printList();
                popLine();
                movement=rand()%8;

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
                //cout << "arriba"<<endl;

                //if(y_/HERO_HEIGHT>0)
            {
                //cout << map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))<<endl;
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
                        //setBanderin(map,lastp);
                    }

                    resultado=true;
                    obstaculo=1;
                    //continue;

                }
                else
                {

                    direction=HERO_UP;
                    movement_stack.push_back(HERO_UP);
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_DOWN;

                    ciclo=true;

                    //ciclo=true;
                }


            }
            break;

            case HERO_DOWN:
                //cout << "abajo"<<endl;
                //                     if(y_/HERO_WIDTH<map_height-1)
                // 					{
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

                else
                {

                    direction=HERO_DOWN;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(HERO_DOWN);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_UP;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                // 					}
                break;

            case HERO_LEFT:
                //cout << "izquierda"<<endl;
                //if(x_/HERO_WIDTH>0)
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

                else
                {

                    direction=HERO_LEFT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(HERO_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                break;


            case HERO_RIGHT:
                //cout << "derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1)
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

                else
                {

                    direction=HERO_RIGHT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(HERO_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                break;

            case UP_RIGHT:
                //cout << "arriba derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1 && y_/HERO_HEIGHT>0)
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

                else
                {

                    direction=UP_RIGHT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(UP_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=DOWN_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }


                break;

            case DOWN_RIGHT:
                //cout << "abajo derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1 && y_/HERO_WIDTH<map_height-1)
            {
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

                else
                {

                    direction=DOWN_RIGHT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(DOWN_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=UP_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
            }

            break;


            case UP_LEFT:
                //cout << "arriba izquierda"<<endl;
                //if(x_/HERO_WIDTH>0 && y_/HERO_HEIGHT>0)
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

                else
                {

                    direction=UP_LEFT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(UP_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=DOWN_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }

                break;

            case DOWN_LEFT:
                //cout << map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)-1)<<endl;

                //if(y_/HERO_WIDTH<map_height-1 &&x_/HERO_WIDTH>0)
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

                else
                {

                    direction=DOWN_LEFT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(DOWN_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=UP_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }


                break;

            case 8://caso extraño que no deberia de llegar aqui, pero sucede y es la unica fora de arreglarlo
                //cout <<"Algo paso"<<endl;
                //popLine();

                bresenham(x_/HERO_WIDTH,y_/HERO_HEIGHT,destx,desty);
                movement=rand()%8;
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
                    obstaculo=0;

                }
                //else
                //    line_stack.erase(line_stack.begin());
                break;

            }
            current_frame++;
        }




    }


    return resultado;
}

int bee::move(vector< string >& map, int heatMap[17][22])
{
    int resultado=false;
    bool ciclo=false;
    int cont=0;
    int movement;
    if(status==STAND)
    {
        movement=rand()%8;
        //printList();

        while(ciclo==false)
        {
            int cont_rep=0;  //contara cuantas veces cae en el random la misma posicion,

            if(cont==30)
            {
                //cout<< "D:"<<endl;
                //printList();
                //popLine();
                movement=rand()%8;

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
                //cout << "arriba"<<endl;

                //if(y_/HERO_HEIGHT>0)
            {
                //cout << map.at((y_/HERO_HEIGHT)-1).at((x_/HERO_WIDTH))<<endl;
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
                        reduceHeat(heatMap,lastp);
                    }

                    resultado=true;
                    obstaculo=1;
                    //continue;

                }
                else
                {

                    direction=HERO_UP;
                    movement_stack.push_back(HERO_UP);
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_DOWN;

                    ciclo=true;

                    //ciclo=true;
                }


            }
            break;

            case HERO_DOWN:
                //cout << "abajo"<<endl;
                //                     if(y_/HERO_WIDTH<map_height-1)
                // 					{
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
                        reduceHeat(heatMap,lastp);
                    }

                    //movement=DOWN_LEFT;
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
                    movement_stack.push_back(HERO_DOWN);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_UP;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                // 					}
                break;

            case HERO_LEFT:
                //cout << "izquierda"<<endl;
                //if(x_/HERO_WIDTH>0)
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
                        reduceHeat(heatMap,lastp);
                    }

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
                    movement_stack.push_back(HERO_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                break;


            case HERO_RIGHT:
                //cout << "derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1)
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
                        reduceHeat(heatMap,lastp);
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
                    movement_stack.push_back(HERO_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=HERO_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
                break;

            case UP_RIGHT:
                //cout << "arriba derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1 && y_/HERO_HEIGHT>0)
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
                        reduceHeat(heatMap,lastp);
                    }

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
                    movement_stack.push_back(UP_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=DOWN_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }


                break;

            case DOWN_RIGHT:
                //cout << "abajo derecha"<<endl;
                //if(x_/HERO_WIDTH<map_width-1 && y_/HERO_WIDTH<map_height-1)
            {
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
                        reduceHeat(heatMap,lastp);
                    }
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
                    movement_stack.push_back(DOWN_RIGHT);
                    //cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=UP_LEFT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }
            }

            break;


            case UP_LEFT:
                //cout << "arriba izquierda"<<endl;
                //if(x_/HERO_WIDTH>0 && y_/HERO_HEIGHT>0)
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
                        reduceHeat(heatMap,lastp);
                    }
                    obstaculo=1;
                    resultado=true;
                    //continue;
                }

                else
                {

                    direction=UP_LEFT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(UP_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=DOWN_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }

                break;

            case DOWN_LEFT:
                //cout << map.at((y_/HERO_HEIGHT)+1).at((x_/HERO_WIDTH)-1)<<endl;

                //if(y_/HERO_WIDTH<map_height-1 &&x_/HERO_WIDTH>0)
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
                        reduceHeat(heatMap,lastp);
                    }
                    obstaculo=1;
                    resultado=true;
                    //continue;
                }

                else
                {

                    direction=DOWN_LEFT;
                    status=MOVEMENT;
                    current_frame=0;
                    animation_frame=0;
                    movement_stack.push_back(DOWN_LEFT);
                    // 							cout <<movement_stack.size()<<endl;
                    lastPosition.x=x_/HERO_WIDTH;
                    lastPosition.y=y_/HERO_HEIGHT;
                    lastp=UP_RIGHT;
                    //line_stack.erase(line_stack.begin());
                    //printList();
                    ciclo=true;
                }


                break;

            case 8://caso extraño que no deberia de llegar aqui, pero sucede y es la unica fora de arreglarlo
                //cout <<"Algo paso"<<endl;
                //popLine();

                //bresenham(x_/HERO_WIDTH,y_/HERO_HEIGHT,destx,desty);
                movement=rand()%8;
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
            y_ += HERO_HEIGHT;
            break;

        case HERO_UP:
            y_ -= HERO_HEIGHT;
            break;

        case HERO_LEFT:
            x_ -= HERO_WIDTH;
            break;

        case HERO_RIGHT:
            x_ += HERO_WIDTH;
            break;

        case UP_RIGHT:
            x_ += HERO_WIDTH ;
            y_ -= HERO_HEIGHT ;
            break;

        case DOWN_RIGHT:
            x_ += HERO_WIDTH ;
            y_ += HERO_HEIGHT ;
            break;

        case UP_LEFT:
            x_ -= HERO_WIDTH ;
            y_ -= HERO_HEIGHT;
            break;

        case DOWN_LEFT:
            x_ -= HERO_WIDTH ;
            y_ += HERO_HEIGHT;
            break;
        }

        if(current_frame<=7)
        {
            switch(current_frame)
            {
            case 0:
            case 4:
                //animation_frame=2;
                //break;

            case 1 :
            case 5:
                //animation_frame=1;
                //break;

            case 2:
            case 6:
                //animation_frame=0;
                //break;

            case 3:
                //animation_frame=1;
                //break;
            case 7:
                //animation_frame=1;
                //movement=16;
                status=STAND;

                if(obstaculo==1)
                {
                    obstaculo=0;

                }
                //else
                //    line_stack.erase(line_stack.begin());
                break;

            }
            //current_frame++;
        }




    }

}


void bee::reduceHeat(int heatMap[17][22], int posicion)
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
    heatMap[lastPosition.y+y][lastPosition.x+x]-=20;
    if(heatMap[lastPosition.y+y][lastPosition.x+x]<=0)
        heatMap[lastPosition.y+y][lastPosition.x+x]=0;
    banderin=true;
}

void bee::move_lastp()
{
    x_=lastPosition.x*32;
    y_=lastPosition.y*32;
}

