#include "building.h"
#include "player.h"
using namespace std;

Building::Building(string name,bool own,int px,int py, Xwindow *w):name(name),own(own),px(px),py(py),w(w) {}

bool Building::getOwn() {return own;}

string Building::getName() {return name;}

//the following methods are meaningless; just don't want to impletement in Unownable
void Building::addNei(Building *b) {}
int Building::getCost() {return 0;}
bool Building::getMort() {return false;}
Player *Building::getOwner() {return NULL;}
void Building::setOwner(int position, Player *p) {}
void Building::improve(int position, std::string s) {
    cout << ">> You can only improve Academic buildings." << endl;
}
void Building::changeImprove(int position, int i) {}
bool Building::isMonopoly() {return false;}
void Building::changeMort(int position, string s) {}
int Building::getPay() {return 0;}
int Building::getLevel() {return 0;}
void Building::auction(int position, vector<Player*>*players, map<string,int>* order, int turn, int numPlayer, bool bankrupt) {}
bool Building::checkNei(){return true;}

bool Building::change(Player *p) {return false;}

Building::~Building() {}

