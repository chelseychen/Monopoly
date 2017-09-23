#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <vector>
#include <map>
class Building;
class Player;
class Xwindow;

class Board {
    Building* m[40];
public:
    Board(bool, Xwindow* w=NULL);
    ~Board();
    Building* pos();
    
    std::string getName(int index);
    bool own(int index);
    Player *getOwner(int index);
    int getCost(int index);
    bool getMort(int index);
    void setOwner(int index, Player *p);
    void improve(int index, std::string s);
    void changeImprove(int index, int i);
    bool isMonopoly(int index);
    void changeMort(int index, std::string s);
    int getPay(int index);
    int getLevel(int index);
    void auction(int index, std::vector<Player*>*players, std::map<std::string,int>* order, int turn, int numPlayer, bool bankrupt=false);
    bool checkNei(int index);

    bool change(int index, Player *p);
};

#endif
