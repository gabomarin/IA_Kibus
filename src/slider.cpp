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

#include "../include/slider.hpp"

slider::slider( int width, int x, int y)
{
    sliderImg=IMG_Load("/resources/sprites/slider.png");
    bar=IMG_Load("resources/sprites/slider_bar.png");
    if(!sliderImg || !bar )
    {
        cout << "no se pudieron cargar recursos" << SDL_GetError()<<endl;
        exit(1);
    }
    this->width=(width/16)*16;
    value=10;
    this->x=x;
    this->y=y;
    font=TTF_OpenFont("resources/visitor1.ttf",18);
    textColor.b=255;
    textColor.g=255;
    textColor.r=255;
    realWidth=this->width+16+33;


    for(int i=0; i<2; ++i)
    {

        frame[i].x=i*sliderImg->w/2;
        frame[i].y=0;
        frame[i].w=sliderImg->w/2;
        frame[i].h=sliderImg->w/2;

    }
    currentFrame=MOUSEOUT;
    clicked=true;

    temp=SDL_CreateRGBSurface(SDL_SWSURFACE, realWidth,20,24,0,0,0,0);
    if(!temp)
    {
        cout << "Error al crear slider "<< SDL_GetError()<<endl;
        exit(1);
    }

}

slider::slider( int width, int value, int x, int y,int min, int max)
{
    sliderImg=IMG_Load("resources/sprites/slider.png");
    bar=IMG_Load("resources/sprites/slider_bar.png");
    if(!sliderImg || !bar )
    {
        cout << "no se pudieron cargar recursos" << SDL_GetError()<<endl;
        exit(1);
    }
    this->width=(width/16)*16;
    if(value<0)
    {
        this->value=0;
    }
    else if(value>100)
    {
        this->value=100;
    }
    else
    {
        this->value=value;
    }
    this->x=x;
    this->y=y;

    font=TTF_OpenFont("resources/visitor1.ttf",18);
    textColor.b=255;
    textColor.g=255;
    textColor.r=255;
    realWidth=this->width+16+33;
    for(int i=0; i<2; ++i)
    {

        frame[i].x=i*sliderImg->w/2;
        frame[i].y=0;
        frame[i].w=sliderImg->w/2;
        frame[i].h=sliderImg->w/2;

    }
    currentFrame=MOUSEOUT;
    this->min=min;
    this->max=max;

    temp=SDL_CreateRGBSurface(SDL_SWSURFACE, realWidth,20,24,0,0,0,0);
    if(!temp)
    {
        cout << "Error al crear slider "<< SDL_GetError()<<endl;
        exit(1);
    }
}

slider::~slider()
{
    SDL_FreeSurface(sliderImg);
    SDL_FreeSurface(bar);
}


int slider::getValue()
{
    return value;
}

void slider::setValue(int value)
{
    if(value<=100 && value>=0)
        this->value=value;
}


SDL_Surface * slider::updateSlider()
{
    //



    SDL_Rect aux;
    string mensaje;

    //	int x;

    SDL_FillRect(temp, 0, SDL_MapRGB(temp->format, 255, 255,0));

    Uint32 colorkey = SDL_MapRGB( temp->format, 255, 255, 0 );
    SDL_SetColorKey( temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey );
    //temp=bar;

    //100 = 240px
    //69= value

    //SDL_FillRect(temp, )

    aux.x=0;
    aux.y=5;
    for(int i=0; i<width/16; ++i)
    {
        aux.x=i*16+12;
        SDL_BlitSurface(bar,NULL,temp,&aux);
    }
    //cout <<"Ancho= "<< width<< endl;
    sliderPos.x=(width*value/100)+4;


    //sliderPos.x-=16;
    //cout << "value= "<<value <<" posicion del slider="<< sliderPos.x <<endl;
    //SDL_Delay(1000);
    sliderPos.y=0;
    SDL_BlitSurface(sliderImg,getFrame(),temp,&sliderPos);


    //Poner el valor del slider
    aux.x=width+25;
    aux.y=sliderPos.y;
    mensaje= lexical_cast<string>(value);
    texto = TTF_RenderText_Solid( font, mensaje.c_str(), textColor );

    SDL_BlitSurface(texto,NULL,temp,&aux);
    SDL_FreeSurface(texto);
    mensaje.clear();
    return temp;



    //slider.x=width/100;

}


int slider::getX()
{
    return x;
}


int slider::getY()
{
    return y;
}


int slider::getWidth()
{
    return width;
}



int slider::getRealWidth()
{
    return realWidth;
}



int slider::handleEvents(SDL_Event event)
{
    int mouse_x,mouse_y; //posicion del mouse
    if( event.type == SDL_MOUSEMOTION ) { //Get the mouse offsets
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;
        //If the mouse is over the button
        if( ( mouse_x > sliderPos.x+x ) && (mouse_x < sliderPos.x+x + (sliderImg->w/2) ) && ( mouse_y > sliderPos.y+y ) && ( mouse_y < sliderPos.y+y + (sliderImg->h) ) )
        {   //Set the button sprite
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
    if(clicked==false) {


        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            //If the left mouse button was pressed
            if( event.button.button == SDL_BUTTON_LEFT )
            {


                mouse_x = event.button.x;
                mouse_y = event.button.y;
                //If the mouse is over the button
                if( ( mouse_x > sliderPos.x+x ) && (mouse_x < sliderPos.x+x + (sliderImg->w/2) ) && ( mouse_y > sliderPos.y+y ) && ( mouse_y < sliderPos.y+y + (sliderImg->h) ) )
                {   //Set the button sprite
                    //Get the mouse offsets
                    clicked=true;
                    startClick= mouse_x = event.button.x;
                    if(mouse_x<x+width &&  mouse_x>x)
                    {
                        sliderPos.x=mouse_x-width;
                    }
                    else if(mouse_x<x)
                    {
                        sliderPos.x=0;
                    }
                    else
                    {
                        sliderPos.x=width;
                    }


                    mouse_y = event.button.y;

                    //cout << "click en el boton" <<endl;
                    return CLICK;

                }


            }

        }
    }
    else if(clicked==true)
    {
        //cout << "Arrastrando" <<endl;
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;
        if(event.type==SDL_MOUSEBUTTONUP)
        {
            endClick= event.button.x;
            if(mouse_x<x+width &&  mouse_x>x)
                sliderPos.x=mouse_x-width;
            else if(mouse_x<x)
            {
                sliderPos.x=0;
            }
            else
            {
                sliderPos.x=width;
            }
            clicked=false;
            return 2;
        }
        if(mouse_x<x+width &&  mouse_x>x)
            sliderPos.x=mouse_x-width;
        else if(mouse_x<x)
        {
            sliderPos.x=0;
        }
        else
        {
            sliderPos.x=width;
        }
        endClick=mouse_x;
        //cout << endClick << endl;
        return 1;

        //If the mouse is over the button
        //if( ( mouse_x > sliderPos.x+x ) && (mouse_x < sliderPos.x+x + (sliderImg->w/2) ) && ( mouse_y > sliderPos.y+y ) && ( mouse_y < sliderPos.y+y + (sliderImg->h) ) )
        //{ //Set the button sprite

        //return CLICK;


        //}
    }

    return 0;
}



void slider::calculateValue()
{
    int temp;
    temp=x+width;
    if(startClick>endClick)
    {
// 		if(endClick<x)
// 		{
// 			endClick=startClick*-1;
// 			endClick=x;
// 		}
// 		temp=startClick-endClick;
// 		sliderPos.x= sliderPos.x-temp;
// 		sliderPos.x=x+startClick-endClick;
// 		cout<<"Arrastre izquierdo "<< startClick-endClick  <<endl;
// 		if(startClick-endClick>=0){
// 		sliderPos.x=startClick-endClick;
// 		cout <<"sliderpos= "<<startClick<< "-"<<endClick<<endl;
//
// 		}
//
// 		else
// 			sliderPos.x=0;
    }
    else if(startClick<endClick)
    {
// 		if(endClick-temp>=0)
// 		{
// 			sliderPos.x=x;
// 		}
// 		else
// 		{
// 			sliderPos.x=x+endClick-startClick;
// 			cout <<"Arrastre derecho " << endClick-startClick;
// 		}
// 		if(endClick-startClick<width){
// 			cout <<"sliderpos= "<<startClick<< "+"<<endClick<<endl;
// 			sliderPos.x=startClick-endClick;
// 		}
//
//
// 		else
// 		sliderPos.x=width;
//
    }

    value=(((sliderPos.x)*100/width));
    //cout <<sliderPos.x<<endl;
    //cout << value<< endl;
    if(value>max)
        value=max;
//
    if(value<min)
        value=min;
    //value*=-1;
    /*


    	value=

    	232=251*X/108*/


    //value=(sliderPos.x*100)/(width);
    if(value>max)
    {
        value=max;
    }
    if(value<min)
    {
        value=min;
    }
    //cout <<value<< "= -("<<sliderPos.x<<"*108) /(-"<<width<<")"<<endl;


}


SDL_Rect * slider::getFrame()
{
    return &frame[currentFrame];
}



