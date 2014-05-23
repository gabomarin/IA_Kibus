#ifndef BEE_H
#define BEE_H

#include "hero.hpp"



class bee : public hero
{
public:
    bee();
    void create(int map_width, int map_height);
    int handle_events(vector< string > &map);
    int move(vector< string >& map, int heatMap[17][22]);
    void reduceHeat(int heatMap[17][22], int posicion);
    void move_lastp();



private:
    int cont;

};


#endif
