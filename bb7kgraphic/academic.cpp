#include "academic.h"
#include "display.h"
#include "player.h"
#include <iostream>
using namespace std;

Academic::Academic(string name, int cost, int pay, string block, int improveCost, int arr[6], int px, int py,int ix,int iy,int ox,int oy, Xwindow *w): Ownable(name,cost,pay,px,py,ix,iy,ox,oy,w), block(block), improveCost(improveCost),level(0){
    for (int i=0; i<6; i++) { levelArr[i] = arr[i]; }
}

int Academic::getLevel() { return level; }

void Academic::improve(int position, string s) {
    if (!isMonopoly()) {
        cout << ">> You don't have the Monopoly Block: " << block << "." << endl;
        cout << ">> You cannot improve " << name << "!" << endl;
    } else {
        bool canImprove = !mort;
        for (int i=0; i<numNei; i++) {
            if (neighbour[i]->getMort()) { canImprove=false; }
        }
        if (canImprove) {
            if (s=="buy") {
                if (level==5) {
                    cout << ">> " << name << " is already WAP!" << endl;
                    cout << ">> You cannot improve more." << endl;
                } else {
                    if (owner->getCash()<improveCost) { // cash is less than improveCost
                        cerr << ">> You don't have enough cash!" << endl;
                    } else {
                        pay = levelArr[++level];
                        owner->setCash(-improveCost);
                        cost += improveCost;
                        getOwner()->getDisplay()->improve(level,position,ix,iy);
                        cout << *(owner->getDisplay());
                        cout << ">> Congradulations!" << endl;
                        cout << ">> " << name << " is level " << level << " now!" << endl;
                        if (level==5) cout << ">> WAP is on. You can use WIFI now." << endl;
                    }
                }
            } else {
                if (level==0) {
                    cout << ">> " << name << " is already level 0!" << endl;
                    cout << ">> You cannot sell any improvement." << endl;
                } else {
                    pay = levelArr[--level];
                    owner->setCash(improveCost/2);
                    cost -= improveCost;
                    getOwner()->getDisplay()->improve(level,position,ix,iy);
                    cout << *(owner->getDisplay());
                    cout << ">> " << name << " is level " << level << " now!" << endl;
                }
            }
        } else {
            cout << ">> Some properties in the Monopoly Block have been mortgaged." << endl;
            cout << ">> You cannot improve " << name << "!" << endl;
        }
    }
}

void Academic::changeImprove(int position, int i) { // using when loading a file
    level=i;
    getOwner()->getDisplay()->improve(i,position,ix,iy);
    if (i==-1) {
        mort=true;
        cost /= 2;
    } else {
        pay=levelArr[i];
        cost += improveCost*level;
    }
}

bool Academic::isMonopoly() {
    for (int i=0; i<numNei; i++) {
        if (neighbour[i]->getOwner() != owner) { return false; }
    }
    return true;
}

int Academic::getPay() {  // add pay to owner's cash. reduce pay from passager in main()
    if (!mort) {
        if (isMonopoly()&&level==0) {
            owner->setCash(2*pay);
            return 2*pay;
        } else {
            owner->setCash(pay);
            return pay;
        }
    } else {
        cout << ">> You don't need to pay tuition for " << name << "!" << endl;
        return 0;
    }
}

void Academic::changeMort(int position, string s) {
    if (s=="mortgage") {
        if (mort) {
            cout << ">> " << name << " has already been mortgaged." << endl;
        } else {
            if (!checkNei()) cout << ">> " << name << " cannot be mortgaged since some properties in its monopoly have improvements." << endl;
            else {
                cost=(cost-improveCost*level)/2;
                owner->setCash(improveCost/2*level+cost);
                level=-1;
                pay=levelArr[0];
                mort=true;
                getOwner()->getDisplay()->improve(-1,position,ix,iy);
                cout << *(owner->getDisplay());
                cout << ">> You mortgaged " << name << "." << endl;
            }
        }
    } else if (s=="unmortgage") {
        if (mort) {
            if (owner->getCash()<cost*1.1) {
                cout << ">> You don't have enough cash to unmortgage " << name << "!" << endl;
            } else {
                owner->setCash(-cost*1.1);
                cost*=2;
                level=0;
                mort=false;
                getOwner()->getDisplay()->improve(0,position,ix,iy);
                cout << *(owner->getDisplay());
                cout << ">> You unmortgaged " << name << "." << endl;
            }
        } else {
            cout << ">> " << name << " has already been unmortgaged." << endl;
        }
    } else {
        mort=false;
        cost*=2;
        level=0;
        getOwner()->getDisplay()->improve(0,position,ix,iy);
        cout << *(owner->getDisplay());
        cout << ">> You unmortgaged " << name << "." << endl;
    }
}

bool Academic::checkNei() {
    for (int i=0; i<numNei; i++) {
        if (neighbour[i]->getLevel()>0) return false;
    }
    return true;
}



Academic::~Academic() {}
