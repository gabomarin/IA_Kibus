#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

#include "include/kimbus.h"
//#include "include/hero.hpp"

int main(int argc, char **argv) {

    kimbus game;
    do
    {
        game.initializeMap();
    } while(game.mainloop()==true);

    return EXIT_SUCCESS;
}
