#include "goose.h"
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

Goose::Goose(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool Goose::change(Player* p) {
    cout << ">> " << p->getName() << " is attacked by a flock of nesting geese!  XD" << endl;
    if (op1) {
        p->setCash(collect);
        setCollect(-1);
    }
    return false;
}

Goose::~Goose() {}
