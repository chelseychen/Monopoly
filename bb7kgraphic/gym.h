#ifndef __GYM_H__
#define __GYM_H__

#if BONUS == no
#include "ownable.h"
#elif BONUS == yes
#include "graphicOwnable.h"
#endif

class Gym: public Ownable {
public:
    Gym(std::string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w);
    virtual int getPay();
    ~Gym();
};

#endif
