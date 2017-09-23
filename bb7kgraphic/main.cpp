#include "display.h"
#include "board.h"
#include "player.h"
#include "building.h"
#include "unownable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;


int main (int argc, char* argv[]) {
    cout << "╔═════════════════════════╗" << endl;
    cout << "║                         ║" << endl;
    cout << "║  Welcome to BB7000 :)   ║" << endl;
    cout << "║                         ║" << endl;
    cout << "╚═════════════════════════╝" << endl;
    
    string action;
    string savedName; // game saved as
    bool test=false;
    bool theme=false;
    if (cin.eof()) return 1;
    if (argc==4) { // loading the theme from a file, might go to test mode
        cout << "=======<< Resume >>========" << endl;
        cout << "<Testing Mode>" << endl;
        cout << "for command 'roll', you can choose your dice number <die1> <die2>" << endl;
        test = true;
        if (*(argv[1]+1) == 'l') { savedName = argv[2]; }
        else { savedName = argv[3]; }
        argc--;
    }
    // initialize board theme from a file or for a new game
    if (argc==3) {
        if (savedName == "") { savedName = argv[2]; }
        ifstream f(savedName.c_str());
        f >> action;
        if (action=="SpecialSave") f >> theme;
    } else {
        cout << "======<< New Game >>=======" << endl;
        cout << "Which board theme do you prefer, University of Waterloo(enter 0) or Disney(enter 1)?" << endl;
        cin >> theme;
        if (cin.eof()) return 1;
    }
    
    TextDisplay* d = new TextDisplay(theme);
    Board* b = new Board(theme);
    
    // VARS
    bool op1 = false;
    bool op2 = false;
    bool op3 = false;
    bool op4 = false;  // player choose to enable bonus rule
    int turn = 0; // set player turns
    int move; // player's move
    string cmd;   // command input
    string who, give, receive;   // used for trade
    string property;// used for improve, mortaged, unmortaged
    bool rolled = false;  // determine rolled or not
    bool saved = false; // check if the current game progress has been saved
    bool AI = false; // implementing AI
    Player* owedPlayer = NULL; // store owing which player
    
    // mapping every human's name with a representing char
    map<string, string> human;
    if (!theme) {
    	human["Goose"] = "G";
    	human["GRT Bus"] = "B";
    	human["Tim Hortons Doughnut"] = "D";
    	human["Professor"] = "P";
    	human["Student"] = "S";
    	human["Money"] = "$";
    	human["Laptop"] = "L";
    	human["Pink tie"] = "T";
    } else {
    	human["Mickey"] = "M";
    	human["Stitch"] = "S";
    	human["Nemo"] = "N";
    	human["Cinderella"] = "C";
    	human["Baymax"] = "B";
    	human["Elsa"] = "E";
    	human["Aladdin"] = "A";
    	human["Dragonslayer"] = "D";
    }
    // mapping every building's name with a position
    map<string, int> buildings;
    for (int i=0; i<40; i++) { buildings[b->getName(i)]=i; }
    vector<Player*> players; // need to be deleted!!!
    map<string, int> playerOrder;
    int numPlayers=1;
    
    // used for options
    Unownable* OSAP=dynamic_cast<Unownable *>(b->pos());
    
    if (argc == 3) {
        string name, c, intTest, building;
        int money, myCups, position, penalty, turns, improve;
        ifstream f(savedName.c_str());
        f >> action;
        if (action!="SpecialSave") {
            stringstream s(action);
            s >> numPlayers;
            // loading players' information
            for (int i=0; i<numPlayers; i++) {
                f >> name >> c;
                while (c.length() > 1) {
                    name.append(" "+c);
                    f >> c;
                }
                while (f >> intTest) {
                    stringstream convert(intTest);
                    if (convert >> money) break;
                    else {
                        name.append(" "+c);
                        c = intTest;
                    }
                }
                f >> myCups >> position;
                if (position==10) {
                    f>>penalty; // check the way by which the player is sent to DC Tims Line
                    if (penalty==1) {
                        f>>turns;
                        Player *p = new Player(test,name,c,b,d,AI,myCups,money,true,turns);
                        p->setPos(position);
                        players.push_back(p);
                    } else {
                        Player *p = new Player(test,name,c,b,d,AI,myCups,money);
                        p->setPos(position);
                        players.push_back(p);
                    }
                } else {
                    Player *p = new Player(test,name,c,b,d,AI,myCups,money);
                    p->setPos(position);
                    players.push_back(p);
                }
                playerOrder[name]=i;
            }
        } else {
            // loading game options
            f >> theme;
            int collect;
            f >> collect;
            OSAP->setCollect(collect);
            f >> op1 >> op2 >> op3 >> op4;
            // loading players' information
            f >> numPlayers >> rolled;
            for (int i=0; i<numPlayers; i++) {
                f >> name >> c;
                while (c.length() > 1) {
                    name.append(" "+c);
                    f >> c;
                }
                while (f >> intTest) {
                    stringstream convert(intTest);
                    if (convert >> money) break;
                    else {
                        name.append(" "+c);
                        c = intTest;
                    }
                }
                f >> AI >> myCups >> position;
                if (position==10) {
                    f>>penalty; // check the way by which the player is sent to DC Tims Line
                    if (penalty==1) {
                        f>>turns;
                        Player *p = new Player(test,name,c,b,d,AI,myCups,money,true,turns);
                        p->setPos(position);
                        players.push_back(p);
                    } else {
                        Player *p = new Player(test,name,c,b,d,AI,myCups,money);
                        p->setPos(position);
                        players.push_back(p);
                    }
                } else {
                    Player *p = new Player(test,name,c,b,d,AI,myCups,money);
                    p->setPos(position);
                    players.push_back(p);
                }
                playerOrder[name]=i;
            }
        }
        // loading buildings' information
        while (f >> building >> name) {
            while (f >> intTest) {
                stringstream convert(intTest);
                if (convert >> improve) break;
                else name.append(" "+intTest);
            }
            if (name!="BANK") { // set owner's pointer to the building
                b->setOwner(buildings[building], players[playerOrder[name]]);
                // add a building's position to the owner's myBuildings
                players[playerOrder[name]]->setMyBuildings(buildings[building]);
                // modify improvement status to a building
                if (improve!=0) { b->changeImprove(buildings[building], improve); }
            }
        }
        saved = true;
    }
    if (argc == 2) {
        cout << "<Testing Mode>" << endl;
        cout << "for command 'roll', you can choose your dice number <die1> <die2>" << endl;
        test = true;
        argc--;
    }
    if (argc == 1) {
        int option = 0;
        while (!(op1 && op2 && op3 && op4)) {
            cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            cout << "┃ You can add rules to the game! (enter '0' to end this selection, '1' to enable option1, etc)     ┃" << endl;
            cout << "┃ You can enable the following rule(s):                                                            ┃" << endl;
            if (!op1) {
            cout << "┃ [Option 1] Money collection from unownable block goes to the center of the board.                ┃" << endl;
            cout << "┃            Landing on Goose Nesting gives a Player all the money in the center.                  ┃" << endl;
            }
            if (!op2) {
            cout << "┃ [Option 2] The above except that the center starts with $500.                                    ┃" << endl;
            cout << "┃            This is replaced if the money is collected.                                           ┃" << endl;
            }
            if (!op3) {
            cout << "┃ [Option 3] Landing on “Collect OSAP” doubles the amount received.                                ┃" << endl;
            }
            if (!op4) {
            cout << "┃ [Option 4] A Player named Bruce Wayne starts with 10 times as much money and owns both MC and DC.┃" << endl;
            }
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            cin >> option;
            if (cin.eof()) {
                delete b;
                delete d;
                return 1;
            }
            if (option == 0) { break; }
            else {
                if (option == 1) { op1 = true; }
                if (option == 2) { op2 = true; }
                if (option == 3) { op3 = true; }
                if (option == 4) { op4 = true; }
            }
        }
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
        cout << "┃ How many players? (2-8) ┃" << endl;
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cin >> numPlayers;
        if (cin.eof()) {
            delete b;
            delete d;
            return 1;
        }
        cin.ignore();
       	vector<string> chose;
        for (int i = 0; i < numPlayers; ++i) {
            cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            cout << "┃ We would like to have your name first: ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            string newName, chosen;
            getline(cin,newName);
            if (cin.eof()) {
                delete b;
                delete d;
                for (int i=0; i<players.size(); i++) { delete players[i]; }
                return 1;
            }
            if (theme) {
            	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            	cout << "┃ Which role do you want to choose? ┃" << endl;
            	cout << "┃ - Mickey (M)                      ┃" << endl;
            	cout << "┃ - Stitch (S)                      ┃" << endl;
            	cout << "┃ - Nemo (N)                        ┃" << endl;
            	cout << "┃ - Cinderella (C)                  ┃" << endl;
            	cout << "┃ - Baymax (B)                      ┃" << endl;
            	cout << "┃ - Elsa (E)                        ┃" << endl;
            	cout << "┃ - Aladdin (A)                     ┃" << endl;
            	cout << "┃ - Dragonslayer (D)                ┃" << endl;
            	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

            }
            else {
            	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            	cout << "┃ Which role do you want to choose? ┃" << endl;
            	cout << "┃ - Goose (G)                       ┃" << endl;
            	cout << "┃ - GRT Bus (B)                     ┃" << endl;
            	cout << "┃ - Tim Hortons Doughnut (D)        ┃" << endl;
            	cout << "┃ - Professor (P)                   ┃" << endl;
            	cout << "┃ - Student (S)                     ┃" << endl;
            	cout << "┃ - Money ($)                       ┃" << endl;
            	cout << "┃ - Laptop (L)                      ┃" << endl;
            	cout << "┃ - Pink tie (T)                    ┃" << endl;
            	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            }
            getline(cin,chosen);
            if (cin.eof()) {
                delete b;
                delete d;
                for (int i=0; i<players.size(); i++) { delete players[i]; }
                return 1;
            }
            bool different = true;
            for (int j = 0; j < chose.size(); ++j) {
                if (chose[j] == chosen) {
                    different = false;
                    cout << ":( Sorry! This role has been chosen." << endl;
                    cout << "Please choose another role." << endl;
                    i--;
                    break;
                }
            }
            if (different) {
                chose.push_back(chosen);
                cout << "Do you prefer to control this role yourself(enter 0) or let computer control it(enter 1)?" << endl;
                cin >> AI;
                if (cin.eof()) {
                    delete b;
                    delete d;
                    for (int i=0; i<players.size(); i++) { delete players[i]; }
                    return 1;
                }
                Player *p = new Player(test,newName, human[chosen], b, d, AI);
                cin.ignore();
                if (op4) {
                    if (newName == "Bruce Wayne") {
                        p->setCash(13500);
                        b->setOwner(37, p);
                        p->setMyBuildings(37);
                        b->setOwner(39, p);
                        p->setMyBuildings(39);
                    }
                }
                players.push_back(p);
                playerOrder[newName]=i;
                cout << "[" << newName << ": " << chosen << "]";
                if (AI) cout << "  -> Computer Player";
                cout << endl;
            }
        }
        if (op2) { // if op2 is still available, initialize the center with $500
            OSAP->setCollect(500);
            cout << "======<<The center starts with $500>>======" << endl;
        }
    }
    OSAP->setOp(op1, op2, op3); // set options to unownable buildings
    
    cout << *d;
    
    while(numPlayers != 1) {
        if (cin.eof()) break;
        if (cmd == "") {
            if (turn == numPlayers)	turn = 0;
            cout << "===================" << endl;
            cout << players[turn]->getName() << "(" << players[turn]->getChar() << ")" << "'s turn now!" << endl;
            cout << "===================" << endl;
        }
        if (players[turn]->getLine()) { // check if the player is in jail
           	cout << ">> You are currently in DC Tims Line, waiting for a cup of coffee." << endl;
       	}
        
        cout << endl;
        cout << players[turn]->getName() << "(" << players[turn]->getChar() << ")" << ", what do you want to do? [Type 'help' for available commands.]" << endl;
   	    if (players[turn]->getAI()) {
            if (players[turn]->getCash() < 0) {
                cmd = "bankrupt";
            } else if (!rolled) {
                cmd = "roll";
            } else {
                cmd = "next";
            }
   	    } else {
            cin >> cmd;
        }
        cout << "======[" << players[turn]->getName() << "(" << players[turn]->getChar() << ")" << " has entered '" << cmd <<  "']======" << endl;
        
        if (cmd != "exit") { saved = false; }
        
        if (cmd == "roll") {
            if (players[turn]->getCash()<0) {
                cout << ">> You are about to bankrupt! You cannot choose 'roll'." << endl;
                cout << ">> You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
                continue;
            }
            if (rolled) {
                cout << ">> You have already rolled." << endl;
                cout << ">> You can enter 'trade', 'mortgage', 'unmortgage', 'improve', 'save', or 'next'." << endl;
            } else {
                if (players[turn]->getLine()) { // check if the player is in jail
                    bool leaveDC = b->change(10, players[turn]);
                    if (leaveDC) {
                        int position = players[turn]->getPos();
                        cout << "[You've moved to " << b->getName(position) << ".]" << endl;
                        owedPlayer = players[turn]->play(position, &players, &playerOrder, turn, numPlayers);
                    }
                    rolled = true;
                } else {
                    move = players[turn]->roll();
                    if (!players[turn]->getLine()) {
                        if (players[turn]->getDoubles()==0) rolled=true;
                        players[turn]->setPos(move);
                        cout << *d;
                        int position = players[turn]->getPos();
                        cout << "[You've moved to " << b->getName(position) << ".]" << endl;
                        owedPlayer = players[turn]->play(position, &players, &playerOrder, turn, numPlayers);
                    }
                    if (players[turn]->getLine()) {// check if the player rolled doubles three times or move to jail
                        turn++;
                        cmd = "";
                        rolled = false;
                    }
                }
            }
        } else if (cmd == "next") {
            if (players[turn]->getCash()<0) {
                cout << ">> Good try! But you cannot choose 'next' since you are about to bankrupt XD" << endl;
                cout << ">> You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
            } else {
                if (!rolled) cout << ">> You need to roll before you choose 'next'." << endl;
                else {
                    turn++;
                    cmd = "";
                    rolled = false;
                }
            }
        } else if (cmd == "trade") {
            if (players[turn]->getCash()<0) {
                cout << ">> You are about to bankrupt! You cannot choose 'trade'." << endl;
                cout << ">> You can sell improvements or mortgage if possible, declare bankrupt otherwise." << endl;
            } else {
                cin.ignore();
                getline(cin,who);
                cin >> give >> receive;
                if (who == players[turn]->getName()) cout << ">> It's not cool to trade with yourself, buddy!" << endl;
                else players[turn]->trade(who, give, receive, &players, &playerOrder, &buildings);
            }
        } else if (cmd == "improve") {
            cin >> property >> action;
            if (b->getOwner(buildings[property]) == players[turn]) {
                b->improve(buildings[property], action);
            } else {
                cout << ">> You don't own this property!" << endl;
            }
        } else if (cmd == "mortgage" || cmd == "unmortgage") {
            cin >> property;
            if (b->getOwner(buildings[property]) == players[turn]) {
                b->changeMort(buildings[property],cmd);
            } else {
                cout << ">> You don't own this property!" << endl;
            }
        } else if (cmd == "bankrupt") {
            cout << ">> " << players[turn]->getName() << " has declared bankruptcy." << endl;
            players[turn]->bankrupt(owedPlayer,&players,&playerOrder,turn,numPlayers);
            delete players[turn];
            players.erase(players.begin()+turn);
            if (turn == --numPlayers) turn = 0;
            cmd = "";
            rolled = false;
        } else if (cmd == "assets") {
            players[turn]->getMyBuilding();
        } else if (cmd == "save") {
            ofstream f;
            cout << ">> Please give a file name to save your game progress." << endl;
            cin >> savedName;
            f.open(savedName.c_str());
            f << "SpecialSave" << endl;
            f << theme << endl;
            f << OSAP->getcollect() << endl;
            f << op1 << " " << OSAP->getOp2() << " " << op3 << " " << op4 << endl;
            f << numPlayers << endl;
            f << rolled << endl;
            for (int i = turn; i-turn < numPlayers; ++i) {
                int j;
                if (i<numPlayers) j=i;
                else j=i-numPlayers;
                f << players[j]->getName() << " "; // name
                f << players[j]->getChar() << " "; // character
                f << players[j]->getCash() << " "; // money
                f << players[j]->getAI() << " ";  // AI
                f << players[j]->getMyCups() << " "; // cups
                f << players[j]->getPos(); // position
                if (players[j]->getPos() == 10) {
                    if (players[j]->getLine()) {
                        f << " 1 " << players[j]->getTurns() << " "; // get the turns that player stay in line
                    } else {
                        f << " 0";
                    }
                }
                f << endl;
            }
            // saving all the information about the properties
            for (int i = 0; i < 40; ++i) {
                if (b->own(i)) {
                    f << b->getName(i) << " ";
                    if (b->getOwner(i)!=NULL) f << b->getOwner(i)->getName() << " ";
                    else f << "BANK ";
                    f << b->getLevel(i) << endl;
                }
            }
            f.close();
            cout << "Current progress has been saved to " << savedName << "." << endl;
            saved = true;
        } else if (cmd == "exit") {
            if (saved) break;
            else {
                cout << ">> You haven't saved the game." << endl;
                cout << ">> Are you sure to quit the game now? (yes/no)" << endl;
                cin >> action;
                if (action=="yes") break;
            }
        } else if (cmd == "help") {
            if (players[turn]->getCash()<0) {
                cout << "[You are about to bankrupt!]" << endl;
                cout << "You're able to enter the following commands only: " << endl;
                cout << "improve <property> sell   - sell an improvement for a property" << endl;
                cout << "mortgage <property>       - mortgage a property" << endl;
                cout << "bankrupt                  - declare bankruptcy (retire from the game)" << endl;
                cout << "assets                    - check your assets" << endl;
                cout << "save <filename>           - save the current game progress to filename" << endl;
                cout << "exit                      - quit the game" << endl;
            } else {
                cout << "You may enter the following commands: " << endl;
                if (!rolled) cout << "roll                          - roll the dice" << endl;
                else cout << "next                          - print the board and end your turn" << endl;
                cout << "trade <name> <give> <receive> - trade name offering give for receive" << endl;
                cout << "improve <property> buy/sell   - buy or sell an improvement for a property" << endl;
                cout << "mortgage <property>           - mortgage a property" << endl;
                cout << "unmortgage <property>         - unmortgage a property" << endl;
                cout << "bankrupt                      - declare bankruptcy (retire from the game)" << endl;
                cout << "assets                        - check your assets" << endl;
                cout << "save <filename>               - save the current game progress to filename" << endl;
                cout << "exit                          - quit the game" << endl;
            }
        } else {
            cout << ">> That is an invalid command, type 'help' to check valid commands." << endl;
        }
    }
    
    // END OF MAIN TURN LOOP
    if (cmd != "exit" && !cin.eof()) {
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
        cout << "┃o(≧v≦)o CONGRATULATIONS! ┃" << endl;
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << players[0]->getName() << "," << endl;
        cout << ">> You win the game!" << endl;
    }
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃  :) See you next time!  ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    
    delete b;
    delete d;
    for (int i=0; i<players.size(); i++) { delete players[i]; }
}


