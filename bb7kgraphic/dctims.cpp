#if BONUS == no
#include "display.h"
#elif BONUS == yes
#include "graphicDisplay.h"
#endif

#include "dctims.h"
#include "player.h"
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

DCTims::DCTims(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool DCTims::change(Player* p) {
    int move;
    int collect = 0;
    string response;
    if (p->getTurns() == 2) {
        cout << ">> You have been here at the third turn." << endl;
        cout << ">> Try to roll doubles :) Good luck to you!" << endl;
        move=p->roll();
        if (!p->getDoubles()) {
            cout << ">> You didn't roll doubles." << endl;
            if (p->getMyCups()) {
                cout << ">> Do you want to use a Tim cup to get coffee for free or pay $50 for it?(cup/pay)" << endl;
                if (p->getAI()) { response = "cup"; }
                else { cin >> response; }
                if (response == "cup") {
                    cout << ">> You used a 'Roll Up the Rim Cup'." << endl;
                    cout << ">> Here's your coffee, you are free to go." << endl;
                    p->changeCups(-1);
                } else {
                    cout << ">> Then you must pay $50 for this coffee now." << endl;
                    p->setCash(-50);
                    collect = 50;
                    cout << ">> You paid $50 for the coffee. Thanks for coming." << endl;
                }
            } else {
                cout << ">> You must pay $50 for this coffee now." << endl;
                p->setCash(-50);
                collect = 50;
                cout << ">> You paid $50 for the coffee. Thanks for coming." << endl;
            }
        }
        if (op1) setCollect(collect);
        p->setLine();
        p->setPos(move);
        cout << *(p->getDisplay());
        if (p->getDoubles()) { cout << ">> You rolled doubles." << endl; }
        cout << ">> You left DC Tims Line." << endl;
        if (p->getCash()<0) {
            cout << "***********************<< You are about to bankrupt >>************************" << endl;
            cout << "You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
        }
        return true;
    } else if (p->getLine()) {
        if (p->getMyCups()) {
            cout << ">> Do you want to use a 'Roll Up the Rim Cup' to get coffee for free? (yes/no)" << endl;
            if (p->getAI()) { response = "yes"; }
            else { cin >> response; }
            if (response == "yes") {
                p->changeCups(-1);
                p->setLine();
                cout << ">> Now You can roll the dice to leave." << endl;
                move=p->roll();
                p->setPos(move);
                cout << *(p->getDisplay());
                cout << ">> You used a 'Roll Up the Rim Cup'." << endl;
                cout << ">> Here's your coffee, you are free to go." << endl;
                cout << ">> You left DC Tims Line." << endl;
                return true;
            }
        }
        cout << ">> Do you want to pay $50 to buy coffee in advance?(yes/no)" << endl;
        if (p->getAI()) { response = "no"; }
        else { cin >> response; }
        if (response == "yes") {
            p->setLine();
            if (p->getCash()<50) { cout << ">> You don't have enough money." << endl;}
            else {
                p->setCash(-50);
                collect = 50;
                cout << ">> Now You can roll the dice to leave." << endl;
                move=p->roll();
                p->setPos(move);
                cout << *(p->getDisplay());
                cout << ">> You paid $50 for the coffee. Thanks for coming." << endl;
                if (op1) setCollect(collect);
                cout << ">> You left DC Tims Line." << endl;
                return true;
            }
        }
        cout << ">> Try to roll doubles :) Good luck to you!" << endl;
        move=p->roll();
        if (p->getDoubles()) {
            p->setLine();
            p->setPos(move);
            cout << *(p->getDisplay());
            cout << ">> You rolled doubles, so you left DC Tims Line." << endl;
            return true;
        } else {
            cout << ">> Ah, you failed to roll doubles. Please keep in line please." << endl;
            p->setTurns(1);
        }
    }
    return false;
}

DCTims::~DCTims() {}
