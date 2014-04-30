#ifndef BEE_H
#define BEE_H

#include "hero.hpp"



class bee : public hero
{
public:
	bee();
	void create(int map_width, int map_height);
	int handle_events(vector< string > &map);
	
	
	
private:
	int cont;
	
};


#endif