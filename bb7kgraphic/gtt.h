#ifndef __GTT_H__
#define __GTT_H__
#include "unownable.h"
#include <string>
class Player;

class GTT: public Unownable {
public:
    GTT(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~GTT();
};



#endif