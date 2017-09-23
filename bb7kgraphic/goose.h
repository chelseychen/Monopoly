#ifndef __GOOSE_H__
#define __GOOSE_H__
#include "unownable.h"
#include <string>
class Player;

class Goose: public Unownable {
public:
    Goose(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~Goose();
};


#endif