#ifndef __UNOWNABLE_H__
#define __UNOWNABLE_H__
#include "building.h"
#include <string>

class Unownable: public Building {
protected:
    static bool op1;
    static bool op2;
    static bool op3;
    static int collect;
public:
	Unownable(std::string name,int px,int py, Xwindow *w);
    void setOp(bool option1, bool option2, bool option3);
    void setCollect(int n);
    int getcollect();
    bool getOp2();
	virtual ~Unownable()=0; //make it abstract
};


#endif