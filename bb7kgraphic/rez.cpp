#include "rez.h"
#include "player.h"
#include <iostream>
using namespace std;

Rez::Rez(string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w):Ownable(name,cost,pay,px,py,ix,iy,ox,oy,w) {}

int Rez::getPay() {
    if (mort) {
        cout << ">> You don't need to pay rent for " << name << "!" << endl;
        return 0;
    } else {
        int n=pay;
        int numRez=1;
        for (int i=0; i<numNei; i++) {
            if (neighbour[i]->getOwner()==owner) {
                n*=2;
                numRez++;
            }
        }
        if (numRez==1) {
            cout << ">> 1 residence is owned by " << owner->getName() << "." << endl;
        } else {
            cout << ">> " << numRez << " residences are owned by " << owner->getName() << "." << endl;
        }
        owner->setCash(n);
        return n;
    }
}

Rez::~Rez() {}