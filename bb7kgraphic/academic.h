#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__

#include "ownable.h"
#include <string>

class Academic: public Ownable {
    std::string block;
    int level,improveCost;
    int levelArr[6];
public:
    Academic(std::string name, int cost, int pay, std::string block, int improveCost, int arr[6], int px, int py,int ix,int iy,int ox,int oy, Xwindow *w);
    virtual int getLevel();
    virtual void improve(int position,std::string s);
    virtual void changeImprove(int position,int i);
    virtual bool isMonopoly();
    virtual int getPay(); // get a single pay from this building
    virtual void changeMort(int position,std::string s);
    virtual bool checkNei();
    ~Academic();
};

#endif