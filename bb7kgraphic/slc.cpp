#if BONUS == no
#include "display.h"
#elif BONUS == yes
#include "graphicDisplay.h"
#endif

#include "slc.h"
#include "player.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

SLC::SLC(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool SLC::change(Player* p) {
    srand(time(NULL));
    if (((rand() % 100) == 1) && (p->getTotalCups() < 4)) {
        p->changeCups(1);
        cout << ">> Congradulations!" << endl;
        cout << ">> You recevive a 'Roll Up the Rim Cup'!" << endl;
        return false;
    } else {
        int chance = rand() % 24;
        int pos = p->getPos();
        if (chance >= 0 && chance <= 2) {
            
            if (pos-3<0) p->setPos(39);
            else p->setPos(pos - 3);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved back 3 spaces to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
                
        } else if (chance >= 3 && chance <= 6) {
            
            p->setPos(pos - 2);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved back 2 spaces to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
            
        } else if (chance >= 7 && chance <= 10) {
            
            p->setPos(pos - 1);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved back 1 space to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
            
        } else if (chance >= 11 && chance <= 13) {
            
            p->setPos(pos + 1);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved forward 1 space to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
            
        } else if (chance >= 14 && chance <= 17) {
            
            p->setPos(pos + 2);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved forward 2 spaces to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
            
        } else if (chance >= 18 && chance <= 21) {
            
            p->setPos(pos + 3);
            cout << *(p->getDisplay());
            cout << "[" << p->getName() << " moved forward 3 spaces to " << p->getBoard()->getName(p->getPos()) << ".]" << endl;
            
        } else if (chance == 22) {
            
            p->setLine();
            p->setPos(10);
            cout << *(p->getDisplay());
            cout << ">> " << p->getName() << ", you have been sent to DC Tims Line." << endl;
            cout << ">> Please wait for the coffee :)" << endl;
            
        } else {
            
            p->setPos(0);
            cout << *(p->getDisplay());
            cout << ">> " << p->getName() << " is advanced to Collect OSAP!" << endl;
            
        }
    }
    return true;
}


SLC::~SLC() {}
