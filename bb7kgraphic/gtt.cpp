#if BONUS == no
#include "display.h"
#elif BONUS == yes
#include "graphicDisplay.h"
#endif

#include "gtt.h"
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

GTT::GTT(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool GTT::change(Player* p) {
    p->setPos(10);
    p->setLine();
    cout << *(p->getDisplay());
    cout << ">> " << p->getName() << ", you have been sent to DC Tims Line." << endl;
    cout << ">> " << "Please wait for the coffee :)" << endl;
    return false;
}

GTT::~GTT() {}