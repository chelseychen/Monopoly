#include "gym.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Gym::Gym(string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w):Ownable(name,cost,pay,px,py,ix,iy,ox,oy,w){}

int Gym::getPay() {
    if (mort) {
        cout << ">> You don't need to pay fee for " << name << "!" << endl;
        return 0;
    } else {
        cout << ">> Please roll the dice to pay." << endl;
        int first, second;
        if (owner->getTest()) {
            cout << "======<< The game is currently in Testing Mode >>======" << endl;
            cout << ">> Please enter the numbers you want to roll." << endl;
            cout << ">> first dice:  ";
            cin >> first;
            cout << ">> second dice: ";
            cin >> second;
            cout << "=======================================================" << endl;
        } else {
            srand(time(NULL));
            first = (rand() % 6) + 1;
            second = (rand() % 6) + 1;
        }
        cout << ">> You rolled " << first << " and " << second << "." << endl;
        cout << ">> The sum of the dice is " << first + second << "." << endl;
        int n = first + second;
        if (neighbour[0]->getOwner()==owner) {
            n*=10;
            cout << ">> Two Gyms are owned by " << owner->getName() << "." << endl;
        }
        else {
            n*=4;
            cout << ">> One Gym is owned by " << owner->getName() << "." << endl;
        }
        owner->setCash(n);
        return n;
    }
}



Gym::~Gym() {}