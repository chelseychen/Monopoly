#ifndef __OSAP_H__
#define __OSAP_H__
#include "unownable.h"
#include <string>
class Player;

class OSAP: public Unownable {
public:
    OSAP(std::string name,int px,int py, Xwindow *w);
    bool change(Player*);
    ~OSAP();
    
};


#endif