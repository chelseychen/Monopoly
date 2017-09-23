#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include <map>
class Board;
class TextDisplay;

class Player {
    std::string name, c;
    // cash: player's current money
    // pos: player's current position
    // doubles: the number of times that player rolled double
    // myCups: the number of player's TimsCups
    // turns: the number of turns that player has been in the DC Tims Line
    // penalty: true if the player if in DC Tims Line; false otherwise
    int cash, pos, doubles, myCups, turns, worthy;
    bool test, penalty, AI;
    static int totalCups;
    Board* b;
    std::vector<int> myBuildings; // recording the positions of buildings that belongs to the player
    TextDisplay* d;
public:
    Player(bool test, std::string name, std::string c, Board* b, TextDisplay* d, bool AI = false, int myCups=0, int cash=1500, bool penalty=false, int turns=0);
    int roll();
    Player* play(int position, std::vector<Player*>*players, std::map<std::string,int>* order, int turn, int numPlayers);
    void trade(std::string who, std::string give, std::string receive, std::vector<Player*>*players, std::map<std::string,int>* order, std::map<std::string, int>*buildings);
    std::string getName();
    std::string getChar();
    TextDisplay* getDisplay();
    Board* getBoard();
    bool getTest();
    int getCash();
    void setCash(int change);
    int getPos();
    void setPos(int position);
    int getDoubles();
    void setDoubles(int n);
    int getTurns();
    void setTurns(int n);
    bool getLine();
    void setLine();
    int getTotalCups();
    int getMyCups();
    void changeCups(int change);
    int getMyBuilding();
    void setMyBuildings(int index);
    void bankrupt(Player* p,std::vector<Player*>*players, std::map<std::string,int>* order, int turn, int numPlayer);
    void ownMort(int index);
    bool getAI();
    ~Player();
};


#endif
