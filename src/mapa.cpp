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

#include "../include/mapa.h"

Mapa::Mapa()
{
	visitado=false;
	
}

Mapa::~Mapa()
{

}

int Mapa::getX()
{
	return x;
}


int Mapa::getY()
{
	return y;
}

bool Mapa::isVisitado()
{
	return visitado;
}


void Mapa::setVisitado(bool visitado)
{
	this->visitado = visitado;
	
}

void Mapa::setX(int x)
{
	this->x= x;
}

void Mapa::setY(int y)
{
	this->y = y;
}


