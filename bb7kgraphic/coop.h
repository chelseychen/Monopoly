#ifndef __COOP_H__
#define __COOP_H__
#include "unownable.h"
#include <string>
class Player;

class Coop: public Unownable {
public:
    Coop(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~Coop();
    
};



#endif