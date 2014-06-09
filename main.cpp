#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

#include "include/kimbus.h"
//#include "include/hero.hpp"

int main(int argc, char **argv) {

    kimbus game;

    game.initializeMap();
    game.mainloop();
	while(true)
	{
    	game.recorrido_entrenado();
	}
    return EXIT_SUCCESS;
}
