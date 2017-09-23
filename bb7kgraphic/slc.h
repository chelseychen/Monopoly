#ifndef __SLC_H__
#define __SLC_H__
#include "unownable.h"
#include <string>
class Player;

class SLC: public Unownable {
public:
	SLC(std::string name,int px,int py, Xwindow *w);
	bool change(Player*);
	~SLC();
	
};



#endif