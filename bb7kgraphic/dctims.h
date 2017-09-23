#ifndef __DCTIMS_H__
#define __DCTIMS_H__
#include "unownable.h"
#include <string>
class Player;

class DCTims: public Unownable {
public:
    DCTims(std::string name,int px,int py, Xwindow *w);
    bool change(Player* p);
    ~DCTims();
    
};



#endif