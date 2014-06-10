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

    animation_frame=2;
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

    animation_frame=0;
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
    anteriorx=0;
    anteriory=0;


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

SDL_Rect hero::obtiene_celda_libre(vector< string >& map, Mapa conexion[17][22], bool &regreso)
{
    SDL_Rect celda,aux;
    vector <SDL_Rect> posibilidades, visitados;
    char tile;
    if( map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH-1)!='A' && map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH-1)!='R' )
    {
        if(anteriorx/HERO_WIDTH!=x_/HERO_WIDTH-1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT-1)
        {
            aux.y=y_/HERO_HEIGHT-1;
            aux.x=x_/HERO_WIDTH-1;
            if(!conexion[y_/HERO_HEIGHT-1][x_/HERO_WIDTH-1].isVisitado()) {


                posibilidades.push_back(aux);
            }
            else
            {
                visitados.push_back(aux);
            }
        }

    }
    tile= map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH);
    if( map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH)!='A' && map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH)!='R' )

    {
        if((anteriorx/HERO_WIDTH!=x_/HERO_WIDTH && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT-1))
        {
            aux.y=y_/HERO_HEIGHT-1;
            aux.x=x_/HERO_WIDTH;
            if(!conexion[y_/HERO_HEIGHT-1][x_/HERO_WIDTH].isVisitado())
            {

                posibilidades.push_back(aux);

            }
            else
            {
                visitados.push_back(aux);
            }
        }

    }

    if( map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH+1)!='A' && map.at(y_/HERO_HEIGHT-1).at(x_/HERO_WIDTH+1)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH+1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT-1))
    {
        aux.y=y_/HERO_HEIGHT-1;
        aux.x=x_/HERO_WIDTH+1;
        if(!conexion[y_/HERO_HEIGHT-1][x_/HERO_WIDTH+1].isVisitado())

        {
            posibilidades.push_back(aux);

        }
        else
        {
            visitados.push_back(aux);
        }
    }

    if( map.at(y_/HERO_HEIGHT).at(x_/HERO_WIDTH-1)!='A' && map.at(y_/HERO_HEIGHT).at(x_/HERO_WIDTH-1)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH-1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT))
    {
        aux.y=y_/HERO_HEIGHT;
        aux.x=x_/HERO_WIDTH-1;
        if(!conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH-1].isVisitado())
        {
            posibilidades.push_back(aux);
        }
        else
        {
            visitados.push_back(aux);
        }
    }



    if( map.at(y_/HERO_HEIGHT).at(x_/HERO_WIDTH+1)!='A' && map.at(y_/HERO_HEIGHT).at(x_/HERO_WIDTH+1)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH+1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT))
    {
        aux.y=y_/HERO_HEIGHT;
        aux.x=x_/HERO_WIDTH+1;
        if(!conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH+1].isVisitado())
        {
            posibilidades.push_back(aux);
        }
        else
        {
            visitados.push_back(aux);
        }

    }

    if( map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH-1)!='A' && map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH-1)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH-1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT+1))
    {
        aux.y=y_/HERO_HEIGHT+1;
        aux.x=x_/HERO_WIDTH-1;
        if(!conexion[y_/HERO_HEIGHT+1][x_/HERO_WIDTH-1].isVisitado())
        {
            posibilidades.push_back(aux);
        }
        else
        {
            visitados.push_back(aux);
        }
    }


    if( map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH)!='A' && map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT+1))
    {
        aux.y=y_/HERO_HEIGHT+1;
        aux.x=x_/HERO_WIDTH;
        if(!conexion[y_/HERO_HEIGHT+1][x_/HERO_WIDTH].isVisitado())
        {
            posibilidades.push_back(aux);
        }
        else
        {
            visitados.push_back(aux);
        }
    }

    if( map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH+1)!='A' && map.at(y_/HERO_HEIGHT+1).at(x_/HERO_WIDTH+1)!='R'
            && (anteriorx/HERO_WIDTH!=x_/HERO_WIDTH+1 && anteriory/HERO_HEIGHT!=y_/HERO_HEIGHT+1))
    {

        aux.y=y_/HERO_HEIGHT+1;
        aux.x=x_/HERO_WIDTH+1;
        if(!conexion[y_/HERO_HEIGHT+1][x_/HERO_WIDTH+1].isVisitado())
        {
            posibilidades.push_back(aux);

        }
        else
        {
            visitados.push_back(aux);
        }
    }

    if(posibilidades.size()>0)
    {
        struct conexion temporal;
        temporal.x=x_/HERO_WIDTH;
        temporal.y=y_/HERO_HEIGHT;
        temporal.peso= MAX_VALUE/2;
        int resultado=rand()%posibilidades.size();
        celda= posibilidades.at(resultado);
        //conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista.push_back(temporal);
    }
    else
    {

        if(x_/HERO_WIDTH!=anteriorx && y_/HERO_HEIGHT!=anteriory && visitados.size()==0)
        {
            celda.x=anteriorx;
            celda.y=anteriory;
        }
        else
        {   /*
            celda=line_stack.back();
            line_stack.pop_back();*/
            regreso=true;

            int resultado=rand()%visitados.size();
            celda= visitados.at(resultado);


        }

    }


    return celda;
}

void hero::clearRecorrido()
{
    int i,j,posicion;
    for(i=0; i<17; i++)
    {
        for(j=0; j<22; j++)
        {
            for(posicion=0; posicion<8; posicion++)
            {
                recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].x=-1;
                recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].y=-1;
                recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectax=-1;
                recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectay= -1;
				recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectay= -1;
				recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].utilizado=false;
            }
        }
    }
    conexiones.clear();
}

int hero:: handle_events(vector <string> &map, Mapa conexion[17][22] )
{

    int resultado=false;
    bool ciclo=false;
    bool regreso=false;
    int cont=0;
    int movement;
    SDL_Rect direccion= obtiene_celda_libre(map, conexion,regreso);
    SDL_Rect temp;
    arista aux;
    anteriorx=x_/HERO_WIDTH;
    anteriory=y_/HERO_HEIGHT;
    if(!regreso)
    {
        temp.x=anteriorx;
        temp.y=anteriory;



        line_stack.push_back(temp);
        //conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista.push_back({x_/HERO_WIDTH, y_/HERO_HEIGHT});
        temp.x=x_/HERO_WIDTH;
        temp.y=y_/HERO_HEIGHT;



    }
    int posicion= calculateDirection(direccion.x, direccion.y);

    //cout << "posicion: "<< posicion<<endl;
    conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].x=x_/HERO_WIDTH;
    conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].y=y_/HERO_WIDTH;
    conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectax=direccion.x;
    conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectay= direccion.y;
    conexion[y_/HERO_HEIGHT][x_/HERO_WIDTH].setVisitado(true);


    recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].x=x_/HERO_WIDTH;
    recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].y=y_/HERO_WIDTH;
    recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectax=direccion.x;
    recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].conectay= direccion.y;
	recorrido[y_/HERO_HEIGHT][x_/HERO_WIDTH].arista[posicion].utilizado=true;
	
	aux.nodo1.x=x_/HERO_WIDTH;
	aux.nodo1.y=y_/HERO_HEIGHT;
	aux.nodo2.x=direccion.x;
	aux.nodo2.y=direccion.y;
	aux.posicion=posicion;
	conexiones.push_back(aux);
    direccion.x *= HERO_WIDTH;
    direccion.y *= HERO_HEIGHT;
    x_=direccion.x;
    y_=direccion.y;
    return true;


}
int hero::cuentaConexiones()
{
	int conexiones=0;
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<22;j++)
		{
			for(int posicion=0;posicion<8;posicion++)
			{
				if(recorrido[i][j].arista[posicion].utilizado==true)
					conexiones++;
			}
		}
	}
	return conexiones;
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

    if(status==STAND)
    {

        switch( movement_stack.back() )
        {
        case HERO_RIGHT:

            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=HERO_RIGHT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;

            break;
        case HERO_LEFT:


            direction=HERO_LEFT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;

            break;

        case HERO_UP:


            direction=HERO_UP;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;


            break;

        case HERO_DOWN:


            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=HERO_DOWN;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;


            break;



        case UP_RIGHT:

            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=UP_RIGHT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;

            break;
        case UP_LEFT:


            direction=UP_LEFT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;

            break;

        case DOWN_RIGHT:


            direction=DOWN_RIGHT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;


            break;

        case DOWN_LEFT:


            //cout <<x_/HERO_WIDTH+1<<endl;
            direction=DOWN_LEFT;
            status=MOVEMENT;
            current_frame=0;
            animation_frame=1;


            break;

        }

    }

    if(status==MOVEMENT		)
    {

        int movement=0;
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
                movement_stack.pop_back();
                break;
            }
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
                y_ += HERO_HEIGHT;
                break;

            case UP_LEFT:
                x_ -= HERO_WIDTH;
                y_ -= HERO_HEIGHT;
                break;

            case DOWN_LEFT:
                x_ -= HERO_WIDTH ;
                y_ += HERO_HEIGHT;
                break;
            }
            //current_frame++;
        }

    }
    return true;

}
void hero::printBack()
{
    cout << "No. Elementos: "<<line_stack.size()<<endl;
    cout << "x: "<<line_stack.back().x<<endl;
    cout << "y: "<<line_stack.back().y<<endl;
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

void hero:: clearStack()
{
    line_stack.clear();
    movement_stack.clear();
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
void hero::eraseBack()
{
    line_stack.pop_back();
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
    //cout <<endl<<endl;

}

void hero::printMovementStack()
{
    for(int i=0; i<movement_stack.size(); i++)
    {
        cout <<movement_stack.at(i)<<endl;

    }
    cout <<endl;
    //cout << endl<< endl;
}



void hero::dropList()
{
    line_stack.clear();
}


int hero::calculateDirection(int destx, int desty)
{
    int movement;
    SDL_Rect hero;
    SDL_Rect temp;
    temp.x=destx;
    temp.y=desty;
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
    //printList();
    popLine();
    //cout <<"Despues "<<endl;
    //printList();
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

int hero::getLastP()
{
    return lastp;
}

void hero::setLastP(int ps)
{
    lastp=ps;
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
    banderin=true;


}
void hero::setFlag(bool flag)
{
    banderin=flag;
}


bool hero::getFlag()
{
    return banderin;
}



bool hero::is_returning()
{
    return returning;
}

void hero::set_returning(bool returning_)
{
    returning=returning_;
}


int hero::get_movement_stack_size()
{
    return movement_stack.size();
}






void hero::setMovement(int dir)
{
    direction=dir;
}




void hero::setStack(vector< int > path)
{
    movement_stack=path;
}


vector <SDL_Rect> hero::getStack()
{
    return line_stack;
}


vector <int> hero:: coordToDir(vector <SDL_Rect> coord)
{
    vector <int> direccion, aux;
    int movement;
    SDL_Rect hero;
    SDL_Rect temp;

    int tempx, tempy;


    //verifica en que direccion debe de ir
    do
    {
        temp= coord.front();
        hero.x=x_/HERO_WIDTH;
        hero.y=y_/HERO_HEIGHT;
        //verifica que tipo de movimiento tendra que hacer
        tempx=hero.x-temp.x;
        tempy=hero.y-temp.y;

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
            cout << "que jodidos!!!!"<<endl;
            movement=8;
        }
        //coord.pop_back();
        coord.erase (coord.begin());
        direccion.push_back(movement);
    } while(!coord.empty());

    do
    {
        aux.push_back( direccion.back());
        direccion.pop_back();
    } while(direccion.size()>0);


    return aux;
}


void hero::setCoordStack(vector< SDL_Rect > movimientos)
{
    line_stack=movimientos;
    //movement_stack=coordToDir();
}


vector< int > hero::getMovementStack()
{
    return movement_stack;
}

int hero::movementBack()
{
    return movement_stack.back();
}


void hero::movementPopBack()
{
    movement_stack.pop_back();
}

void hero::movementPushBack(int movimiento)
{
    movement_stack.push_back(movimiento);
}




