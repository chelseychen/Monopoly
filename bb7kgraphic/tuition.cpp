#include "tuition.h"
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

Tuition::Tuition(string name,int px,int py, Xwindow *w): Unownable(name,px,py,w) {}

bool Tuition::change(Player* p) {
    cout << ">> You need to pay tuition to the University. Please choose a way to pay:" << endl;
    cout << ">> enter '1': pay $300." << endl;
    cout << ">> enter '0': pay 10% of your total assets." << endl;
    int response;
    if (p->getAI()) { response = 0; }
    else cin >> response;
    if (response) {
        cout << ">> You chose to pay $300 tuition to University." << endl;
        p->setCash(-300);
        response = 300;
    } else {
        cout << ">> You chose to pay 10% of your total assets for tuition to the University." << endl;
        response = p->getMyBuilding();
        response *= 0.1;
        cout << ">> So you paid $" << response << " to the University." << endl;
        p->setCash(-response);
    }
    if (p->getCash()<0) {
        cout << "***********************<< You are about to bankrupt >>************************" << endl;
        cout << "You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
    }
    if (op1) { setCollect(response); }
    return false;
}

Tuition::~Tuition() {}
