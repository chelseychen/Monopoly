#ifndef __REZ_H__
#define __REZ_H__

#if BONUS == no
#include "ownable.h"
#elif BONUS == yes
#include "graphicOwnable.h"
#endif

class Rez: public Ownable {
public:
    Rez(std::string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w);
    virtual int getPay();
    ~Rez();
};

#endif
