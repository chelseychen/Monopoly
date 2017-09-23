#include "OSAP.h"
#include "player.h"
#include <iostream>
#include <string>

using namespace std;

OSAP::OSAP(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool OSAP::change(Player* p) {
    if (op3) {
        cout << ">> Lucky you! :) Just land on the right place!" << endl;
        cout << ">> Get your $400! Good good study day day up!" << endl;
        p->setCash(400);
    } else {
        cout << ">> Oh, you just land on the right place! However, no option, no difference!:(" << endl;
        cout << ">> We'll support $200 for your study!" << endl;
        p->setCash(200);
    }
    return false;
}

OSAP::~OSAP() {}