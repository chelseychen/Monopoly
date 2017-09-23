#if BONUS == no
#include "display.h"
#elif BONUS == yes
#include "graphicDisplay.h"
#endif

#include "player.h"
#include "board.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
using namespace std;

int Player::totalCups = 0;

Player::Player(bool test, string name, string c, Board* b, TextDisplay* d, bool AI, int myCups, int cash, bool penalty, int turns): test(test),
 name(name), c(c), b(b), d(d), AI(AI), myCups(myCups), cash(cash), penalty(penalty), turns(turns), pos(0), doubles(0) {
    totalCups+=myCups;
    d->addPlayer(c);
}

int Player::roll() {
    int first, second;
    if (test && !AI) {
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
    if (first == second) {
        doubles++;
        cout << ">> You rolled doubles." << endl;
        if (doubles==3) {
            setLine();
            setPos(10);
            cout << *d;
            cout << ">> You have been sent to DC Tims Line." << endl;
            cout << ">> Please wait for the coffee :)" << endl;
        }
    } else {
        doubles = 0;
    }
    return pos + first + second;
}

Player* Player::play(int position, vector<Player*>*players, map<string,int>* order, int turn, int numPlayers) {
    if (b->own(position)) { // check ownable or unownable
        if (b->getOwner(position)!=NULL) { // check if the property has an owner
            if (b->getOwner(position)!=this) { // check if the owner is not current player
                int pay = b->getPay(position);
                setCash(-pay);
                cout << ">> " << name << " paid $" << pay << " to " << b->getOwner(position)->getName() << "." << endl;
                if (getCash()<0) {
                    cout << "***********************<< You are about to bankrupt >>************************" << endl;
                    cout << "You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
                    return b->getOwner(position);// The player owed the property's owner money
                }
                else cout << ">> " << name << " has $" << getCash() << " left." << endl;
            }
        } else {
            cout << ">> You currently have $" << getCash() << "." << endl;
            cout << ">> Do you want to buy " << b->getName(position) << "($" << b->getCost(position) << ")? (yes/no)" << endl;
            string action;
            if (AI) { action = "yes"; }
            else { cin >> action; }
            if (action=="yes") {
                if (getCash()<b->getCost(position)) {
                    cout << ">> You don't have enough money to buy " << b->getName(position) << "." << endl;
                } else {
                    b->setOwner(position, this);
                    setMyBuildings(position);
                    setCash(-(b->getCost(position)));
                    cout << ">> " << getName() << " bought " << b->getName(position) << "." << endl;
                    return NULL;
                }
            }
            b->auction(position, players, order, turn, numPlayers);
        }
    } else {
        bool isSLC = b->change(position, this);
        if (isSLC && !getLine()) {
            play(getPos(), players, order, turn, numPlayers);
        }
    }
    return NULL;
}

void Player::trade(string who, string give, string receive, vector<Player*>*players, map<string,int>* order, map<string, int>*buildings) {
    int result; // used to store the int that convert from string
    stringstream convert1(give);  // stringstream used to convert string to int
    stringstream convert2(receive);
    string action, property;
    Player* getMoney=NULL;
    Player* getProperty=NULL;
    
    if (convert1 >> result)  { // if give is integer, true, false otherwise
        // if give is integer. receice can't be integer, meaningless otherwise
        
        if (b->getLevel((*buildings)[receive]) > 0) cout << ">> You cannot ask for an improved building." << endl;
        else if (!b->checkNei((*buildings)[receive])) cout << ">> You cannot ask for " << receive << " because some properties in its monopoly have improvements." << endl;
        else if (getCash() < result) cout << ">> You don't have enough money to trade, please check your cash." << endl;
        else {
            cout << ">> " << getName() << " offered $" << give << " to " << who << " for " << receive << "." << endl;
            cout << ">> " << who << ", do you accept? (yes/no)" << endl;
            if ((*players)[(*order)[who]]->getAI()) action = "no";
            else cin >> action;
            if (action=="yes") {
                cout << ">> " << getName() << ", you got " << receive << " from " << who << " by $" << result << "." << endl;
            }
            property = receive;
            getMoney = (*players)[(*order)[who]];
            getProperty = this;
        }
        
    } else if (convert2 >> result) { // give is not int, check for receive
        
        if (b->getLevel((*buildings)[give]) > 0) cout << ">> You cannot give an improved building to others." << endl;
        else if (!b->checkNei((*buildings)[give])) cout << ">> You cannot give " << give << " because some properties in its monopoly have improvements." << endl;
        else if ((*players)[(*order)[who]]->getCash() < result) cout << ">> " << who << " don't have enough money to trade." << endl;
        else {
            cout << ">> " << getName() << " offered " << give << " to " << who << " for $" << receive << "." << endl;
            cout << ">> " << who << ", do you accept? (yes/no)" << endl;
            if ((*players)[(*order)[who]]->getAI()) action = "no";
            else cin >> action;
            if (action=="yes") {
                cout << ">> " << getName() << ", you sold " << receive << " to " << who << " for $" << result << "." << endl;
            }
            property = give;
            getMoney = this;
            getProperty = (*players)[(*order)[who]];
        }
        
    } else { // both of them are buildings
        
        if (b->getLevel((*buildings)[receive]) > 0) cout << ">> You can't ask for an improved building." << endl;
        else if (b->getLevel((*buildings)[give]) > 0) cout << ">> You can't give an improved building to others." << endl;
        else if (!b->checkNei((*buildings)[receive])) cout << ">> You can't ask for " << receive << " because some properties in its monopoly have improvements." << endl;
        else if (!b->checkNei((*buildings)[give])) cout << ">> You can't give " << give << " because some properties in its monopoly have improvements." << endl;
        else {
            cout << ">> " << getName() << " offered " << give << " to " << who << " for " << receive << "." << endl;
            cout << ">> " << who << ", do you accept? (yes/no)" << endl;
            if ((*players)[(*order)[who]]->getAI()) action = "no";
            else cin >> action;
            if (action=="yes") {
                b->setOwner((*buildings)[give], (*players)[(*order)[who]]);
                setMyBuildings((*buildings)[give]);
                (*players)[(*order)[who]]->setMyBuildings((*buildings)[give]);
                b->setOwner((*buildings)[receive], this);
                setMyBuildings((*buildings)[receive]);
                (*players)[(*order)[who]]->setMyBuildings((*buildings)[receive]);
                cout << ">> " << getName() << " traded "<< give << " to " << who << " for " << receive << "." << endl;
                if (b->getMort((*buildings)[receive])) { ownMort((*buildings)[receive]); }
                if (b->getMort((*buildings)[give])) { (*players)[(*order)[who]]->ownMort((*buildings)[give]); }
                return;
            }
        }
    }
    
    if (action=="no") cout << ">> " << who << " refused the trade from " << getName() << "." << endl;
    if (action=="yes") {
        getMoney->setCash(result);
        getProperty->setCash(-result);
        b->setOwner((*buildings)[property], getProperty);
        getMoney->setMyBuildings((*buildings)[property]);
        getProperty->setMyBuildings((*buildings)[property]);
        if (b->getMort((*buildings)[property])) { getProperty->ownMort((*buildings)[property]); }
    }

}

bool Player::getTest() { return test; }

string Player::getName() { return name; }

string Player::getChar() { return c; }

TextDisplay* Player::getDisplay() { return d; }

Board* Player::getBoard() { return b; }

int Player::getCash() { return cash; }

void Player::setCash(int change) { cash += change; }

int Player::getPos() { return pos; }

void Player::setPos(int position) {
    if (position>40) {
        pos=position-40;
        setCash(200);
        cout << ">> You passed Collect OSAP :)" << endl;
        cout << ">> You collected $200." << endl;
    } else if (position==40) {
        pos = 0;
    } else {
        pos=position;
    }
    d->changePosition(c, pos);
}

int Player::getDoubles() { return doubles; }

void Player::setDoubles(int n) {
    if (n) doubles++;
    else doubles=0;
}

int Player::getTurns() { return turns; }

void Player::setTurns(int n) {
    if (n) { turns++; }
    else turns = 0;
}

bool Player::getLine() { return penalty; }

void Player::setLine() {
    penalty = !penalty;
    doubles = 0;
    turns = 0;
}

int Player::getTotalCups() { return totalCups; }

int Player::getMyCups() { return myCups; }

// change the total number of cups and the number of player's cups
// change can be +1 or -1
void Player::changeCups(int change) {
    totalCups+=change;
    myCups+=change;
}

int Player::getMyBuilding() {
    cout << "======<< Here are your assets >>======" << endl;
    cout << "You currently have $" << cash << endl;
    cout << "Properties:" << endl;
    int value = cash;
    if (myBuildings.size()==0) {
        cout << "None" << endl;
    } else {
        for (int i=0; i<myBuildings.size(); i++) {
            cout << b->getName(myBuildings[i]) << ": ";
            if (b->getMort(myBuildings[i])) cout << "Mortgaged   ";
            else cout << "Unmortgaged   ";
            cout << "[value: " << b->getCost(myBuildings[i]) << "]" << endl;
            value+=b->getCost(myBuildings[i]);
        }
    }
    cout << "The total value of your assets: $" << value << "." << endl;
    cout << "======================================" << endl;
    return value;
}

void Player::setMyBuildings(int index) {
    for (int i = 0; i < myBuildings.size(); ++i) {
        if (myBuildings[i] == index) {
            myBuildings.erase(myBuildings.begin() + i);
            return;
        }
    }
    myBuildings.push_back(index);
}

void Player::bankrupt(Player* p,vector<Player*>*players, map<std::string,int>* order, int turn, int numPlayer) {
    changeCups(-myCups);
    if (p==NULL) {
        for (int i=0; i<myBuildings.size(); i++) {
            b->auction(myBuildings[i], players, order, turn, numPlayer, true);
        }
    } else {
        p->setCash(cash);
        for (int i=0; i<myBuildings.size(); i++) {
            b->setOwner(myBuildings[i], p);
            if (b->getMort(myBuildings[i])) {
                p->ownMort(myBuildings[i]);
            }
        }
    }
}

void Player::ownMort(int index) {
    string action;
    cout << ">> " << name << ", you've been the owner of " << b->getName(index) << "." << endl;
    cout << ">> You have to pay 10% to the Bank since " << b->getName(index) << " is a mortgaged building." << endl;
    setCash(-b->getCost(index)*0.1);
    cout << ">> Do you want to unmortgage the property by paying the principle now? (yes/no)" << endl;
    cout << "[Notes: If you choose to leave the property mortgaged, you will have to pay an additional 10% later when you decide to unmortgage it.]" << endl;
    if (AI) action = "yes";
    else cin >> action;
    if (action=="yes") {
        if (cash<b->getCost(index)) {
            cout << ">> You cannot unmortgage " << b->getName(index) << " now since you don't have enough money." << endl;
        } else {
            setCash(-b->getCost(index));
            b->changeMort(index, "unmortgage(new)");
        }
    } else {
        cout << ">> You've left " << b->getName(index) << " mortgaged." << endl;
    }
}

bool Player::getAI() { return AI; }

Player::~Player() {}





