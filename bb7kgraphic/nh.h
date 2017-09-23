#ifndef __NH_H__
#define __NH_H__
#include "unownable.h"
#include <string>
class Player;

class NH: public Unownable {
public:
    NH(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~NH();
    
};



#endif