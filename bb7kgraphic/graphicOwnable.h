#ifndef __GRAPHICOWNABLE_H__
#define __GRAPHICOWNABLE_H__

#include "building.h"
#include <string>
#include <map>
#include <vector>
class Player;

class Ownable: public Building {
protected:
    int ix,iy,ox,oy; // coordiinates of improve(mort)&owner
    int cost,pay;
    bool mort;
    Player *owner;
    Building *neighbour[3]; //
    int numNei;
public:
    Ownable(std::string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w);
    virtual void addNei(Building *b);
    virtual int getCost();
    virtual bool getMort();
    virtual Player *getOwner();
    virtual void setOwner(int position, Player *p);
    virtual int getLevel();
    virtual void changeImprove(int position, int level);
    virtual void changeMort(int position, std::string);
    ~Ownable();
    /*
     virtual void improve(int position, std::string s);
     virtual bool isMonopoly();
     
     
     virtual int getPay()=0;
     */
    void auction(int position, std::vector<Player*>*players, std::map<std::string,int>* order, int turn, int numPlayer, bool bankrupt=false);
};

#endif
