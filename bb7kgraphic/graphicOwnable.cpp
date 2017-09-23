#include "graphicOwnable.h"
#include "graphicDisplay.h"
#include "player.h"
#include "window.h"
using namespace std;

Ownable::Ownable(string name,int cost,int pay,int px,int py,int ix,int iy,int ox,int oy, Xwindow *w):Building(name,true,px,py,w),cost(cost),pay(pay),mort(false),owner(NULL),numNei(0),ix(ix),iy(iy),ox(ox),oy(oy) {}

void Ownable::addNei(Building *b) { neighbour[numNei++]=b; }

int Ownable::getCost(){ return cost; }

bool Ownable::getMort() { return mort; }

Player* Ownable::getOwner() { return owner; }

void Ownable::setOwner(int position, Player *p) {
    if ((owner!=NULL)&&(w!=NULL)) w->drawString(ox,oy,"("+owner->getChar()+")",w->getColour(position));
    owner = p;
    if (w!=NULL) w->drawString(ox,oy,"("+owner->getChar()+")",1);
}

int Ownable::getLevel() {
    if (mort) { return -1; }
    else return 0;
}

void Ownable::changeImprove(int position, int i) { // i can only be -1 // using when loading a file
    mort=true;
    cost /= 2;
    getOwner()->getDisplay()->improve(-1,position,ix,iy);
}

void Ownable::changeMort(int position,string s) {
    if (s=="mortgage") {
        if (mort) {
            cout << ">>" << name << " has already been mortgaged." << endl;
        } else {
            cost /= 2;
            owner->setCash(cost);
            mort=true;
            getOwner()->getDisplay()->improve(-1,position,ix,iy);
            cout << *(owner->getDisplay());
            cout << ">> You mortgaged " << name << "." << endl;
        }
    } else if (s=="unmortgage") {
        if (mort) {
            if (owner->getCash()<cost*1.1) {
                cout << ">> You don't have enough cash to unmortgage " << name << "!" << endl;
            } else {
                owner->setCash(-cost*1.1);
                cost *= 2;
                mort=false;
                getOwner()->getDisplay()->improve(0,position,ix,iy);
                cout << *(owner->getDisplay());
                cout << ">> You unmortgaged " << name << "." << endl;
            }
        } else {
            cout << ">>" << name << " has already been unmortgaged." << endl;
        }
    } else {
        mort=false;
        cost*=2;
        getOwner()->getDisplay()->improve(0,position,ix,iy);
        cout << *(owner->getDisplay());
        cout << ">> You unmortgaged " << name << "." << endl;
    }
}

Ownable::~Ownable() {}

void Ownable::auction(int position, vector<Player*>*players, map<string,int>* order, int turn, int numPlayer, bool bankrupt) {
    cout << "========<< " << name << " is going to be auctioned >>======" << endl;
    int bidPrice = 0;
    string action;
    vector<string> auctionPlayer(numPlayer);
    for (int i = 0; i < numPlayer; ++i) { auctionPlayer[i] = (*players)[i]->getName(); }
    //if the property is being auctioned due to bankrupt, the current owner would not participate in the auction
    if (bankrupt) {
        auctionPlayer.erase(auctionPlayer.begin() + turn);
        numPlayer--;
    }
    while (numPlayer != 1) {
        if (turn == numPlayer) turn = 0;
        if ((*players)[turn]->getCash()<bidPrice+1) {
            cout << ">> " << auctionPlayer[turn] << " didn't have enough money to bid and left auction." << endl;
            auctionPlayer.erase(auctionPlayer.begin() + turn);
            numPlayer--;
            continue;
        }
        cout << "[" << auctionPlayer[turn] << "'s turn]: minimum bid price is $" << bidPrice+1 << ",  bid or forbid?" << endl;
        if ((*players)[turn]->getAI()) {
            if (bidPrice < 100) action = "bid";
            else action = "forbid";
        } else {
            cin >> action;
        }
        if (action == "bid") {
            int minBid = bidPrice+1;
            cout << ">> Enter your bid price:" << endl;
            if ((*players)[turn]->getAI()) bidPrice++;
            else cin >> bidPrice;
            if (bidPrice < minBid || bidPrice>(*players)[turn]->getCash()) {
                cout << ">> It's not a valid bid price. Please enter another price or leave auction." << endl;
                bidPrice = minBid-1;
                continue;
            }
            cout << ">> " << (*players)[turn]->getName() << " entered price: " << bidPrice << endl;
            turn++;
        } else {
            cout << ">> " << auctionPlayer[turn] << " left auction." << endl;
            auctionPlayer.erase(auctionPlayer.begin() + turn);
            numPlayer--;
        }
    }
    if (bidPrice==0) { bidPrice=1; }
    int winner = (*order)[auctionPlayer[0]];
    cout << ">> Congradulations! " << auctionPlayer[0] << " is the winner." << endl;
    cout << ">> " << auctionPlayer[0] << " got " << name << " at $" << bidPrice << "." << endl;
    (*players)[winner]->setCash(-bidPrice);
    setOwner(position, (*players)[winner]);
    (*players)[winner]->setMyBuildings(position);
    if (mort) { owner->ownMort(position); }
}


