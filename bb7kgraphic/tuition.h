#ifndef __TUITION_H__
#define __TUITION_H__
#include "unownable.h"
#include <string>
class Player;

class Tuition: public Unownable {
public:
    Tuition(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~Tuition();
    
};


#endif