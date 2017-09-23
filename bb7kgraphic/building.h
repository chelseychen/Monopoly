#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <string>
#include <vector>
#include <iostream>
#include <map>
class Player;
class Xwindow;

class Building {
protected:
    Xwindow *w;
    std::string name;
    bool own;
    // graphic field: players
    int px,py;
public:
    Building(std::string name, bool own, int px, int py, Xwindow *w);
    bool getOwn();
    std::string getName();
    
    // the following methods are with respect to ownable
    virtual void addNei(Building *b);
    virtual int getCost();
    virtual bool getMort();
    virtual Player *getOwner();
    virtual void setOwner(int position, Player *p);
    virtual void improve(int position, std::string s);
    virtual void changeImprove(int position, int i);
    virtual bool isMonopoly();
    virtual void changeMort(int position, std::string s);
    virtual int getPay();
    virtual int getLevel();
    virtual void auction(int position, std::vector<Player*>*players, std::map<std::string,int>* order, int turn, int numPlayer, bool bankrupt=false);
    virtual bool checkNei();
    
    // This method is with respect to unownable
    virtual bool change(Player *p);
    
    virtual ~Building()=0;//make Building abstract
    
    
};

#endif