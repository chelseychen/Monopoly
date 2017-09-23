#include "coop.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Coop::Coop(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool Coop::change(Player* p) {
    cout << ">> You paid $150 as coop fee to the University." << endl;
    p->setCash(-150);
    if (p->getCash()<0) {
        cout << "***********************<< You are about to bankrupt >>************************" << endl;
        cout << "You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
    }
    if (op1) { setCollect(150); }
    return false;
}

Coop::~Coop() {}
