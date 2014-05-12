#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

#include "include/kimbus.h"
//#include "include/hero.hpp"

int main(int argc, char **argv){
	
	kimbus game;
    bool ciclo=false;
    do
    {    
	    game.initializeMap();
        ciclo= game.mainloop();
    }while(ciclo==true);
    
	
	return EXIT_SUCCESS;
}
