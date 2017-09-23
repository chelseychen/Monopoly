#include "nh.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

NH::NH(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool NH::change(Player* p) {
    srand(time(NULL));
    if (((rand() % 100) == 1) && (p->getTotalCups() < 4)) {
        p->changeCups(1);
        cout << ">> Congradulations!" << endl;
        cout << ">> You recevive a 'Roll Up the Rim Cup'!" << endl;
    } else {
        int chance = rand() % 18;
        if (chance == 0) {
            
            cout << ">> So sad! You fail a course, you need to pay $200 to retake it. D:" << endl;
            p->setCash(-200);
            
        } else if (chance >= 1 && chance <= 2) {
            
            cout << ">> Oh, no! There is an accident, your textbook burnt by fire, need $100 to buy a new one." << endl;
            p->setCash(-100);
            
        } else if (chance >= 3 && chance <= 5) {
            
            cout << ">> You need to pay for insurance to make sure you have a safe school life, cost $50" << endl;
            p->setCash(-50);
            
        } else if (chance >= 6 && chance <= 11) {
            
            cout << ">> You have won the first prize in the Euclid Mathmatic Contest, gained $25!" << endl;
            p->setCash(25);
            
        } else if (chance >= 12 && chance <= 14) {
            
            cout << ">> Tax refund, collect $50!" << endl;
            p->setCash(50);
            
        } else if (chance >= 15 && chance <= 16) {
            
            cout << ">> Bike got stolen, insurance paid you for a new one at $100!" << endl;
            p->setCash(100);
            
        } else {
            
            cout << ">> University error in your favor $200! :D" << endl;
            p->setCash(200);
            
        }
    }
    if (p->getCash()<0) {
        cout << "***********************<< You are about to bankrupt >>************************" << endl;
        cout << "You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
        
    }
    return false;
}

NH::~NH() {}
