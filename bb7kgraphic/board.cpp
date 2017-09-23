#if BONUS == no
#include "academic.h"
#include "ownable.h"
#elif BONUS == yes
#include "academiceven.h"
#include "graphicOwnable.h"
#endif

#include "board.h"
#include "rez.h"
#include "gym.h"
#include "unownable.h"
#include "tuition.h"
#include "slc.h"
#include "OSAP.h"
#include "nh.h"
#include "gtt.h"
#include "goose.h"
#include "dctims.h"
#include "coop.h"
#include <string>
using namespace std;

Board::Board(bool theme, Xwindow* w) {
    int tuition[16][6]= {{2,10,30,90,160,250},{4,20,60,180,320,450},{6,30,90,270,400,550},{8,40,100,300,450,600},{10,50,150,450,625,750},{12,60,180,500,700,900},{14,70,200,550,750,950},{16,80,220,600,800,1000},{18,90,250,700,875,1050},{20,100,300,750,925,1100},{22,110,330,800,975,1150},{24,120,360,850,1025,1200},{26,130,390,900,1100,1275},{28,150,450,1000,1200,1400},{35,175,500,1100,1300,1500},{50,200,600,1400,1700,2000}};
	if (theme) {
        m[5] = new Rez("Dumbo",200,25,258,555,258,525,289,525,w);
        m[15] = new Rez("Bambi",200,25,3,300,3,270,34,270,w);
        m[25] = new Rez("ToyStory",200,25,258,45,258,15,289,15,w);
        m[35] = new Rez("Tangled",200,25,513,300,513,270,544,270,w);
    
        // initialize 2 gyms
        m[12] = new Gym("Pooh",150,0,3,453,3,423,34,423,w);
        m[28] = new Gym("Popeye",150,0,411,45,411,15,442,15,w);
    
        // initialize "Arts1"
        m[1] = new Academic("TRON",40,2,"Arts1",50,tuition[0],462,555,462,525,493,525,w);
        m[3] = new Academic("Up",60,4,"Arts1",50,tuition[1],360,555,360,525,391,525,w);
    
        // initialize "Arts2"
        m[6] = new Academic("Mulan",100,6,"Arts2",50,tuition[2],207,555,207,525,238,525,w);
        m[8] = new Academic("Oz",100,6,"Arts2",50,tuition[2],105,555,105,525,136,525,w);
        m[9] = new Academic("Genius",120,8,"Arts2",50,tuition[3],54,555,54,525,85,525,w);
    
        // initialize "Eng"
        m[11] = new Academic("PeterPan",140,10,"Eng",100,tuition[4],3,504,3,474,34,474,w);
        m[13] = new Academic("AirBud",140,10,"Eng",100,tuition[4],3,402,3,372,34,372,w);
        m[14] = new Academic("Dinosaur",160,12,"Eng",100,tuition[5],3,351,3,321,34,321,w);
    
        // initialize "Health"
        m[16] = new Academic("Brave",180,14,"Health",100,tuition[6],3,249,3,219,34,219,w);
        m[18] = new Academic("SnowDogs",180,14,"Health",100,tuition[6],3,147,3,117,34,117,w);
        m[19] = new Academic("Holes",200,16,"Health",100,tuition[7],3,96,3,66,34,66,w);
    
        // initialize "Env"
        m[21] = new Academic("Atlantis",220,18,"Env",150,tuition[8],54,45,54,15,85,15,w);
        m[23] = new Academic("Caribean",220,18,"Env",150,tuition[8],156,45,156,15,187,15,w);
        m[24] = new Academic("Frozen",240,20,"Env",150,tuition[9],207,45,207,15,238,15,w);
    
        // initialize "Sci1"
        m[26] = new Academic("Miracle",260,22,"Sci1",150,tuition[10],309,45,309,15,340,15,w);
        m[27] = new Academic("LionKing",260,22,"Sci1",150,tuition[10],360,45,360,15,391,15,w);
        m[29] = new Academic("Valiant",280,24,"Sci1",150,tuition[11],462,45,462,15,493,15,w);
    
        // initialize "Sci2"
        m[31] = new Academic("TheWild",300,26,"Sci2",200,tuition[12],513,96,513,66,544,66,w);
        m[32] = new Academic("Underdog",300,26,"Sci2",200,tuition[12],513,147,513,117,544,117,w);
        m[34] = new Academic("Bolt",320,28,"Sci2",200,tuition[13],513,249,513,219,544,219,w);
    
        // initialize "Math"
        m[37] = new Academic("Cars",350,35,"Math",200,tuition[14],513,402,513,372,544,372,w);
        m[39] = new Academic("Planes",400,50,"Math",200,tuition[15],513,504,513,474,544,474,w);
    
        // initialize all unownable buildings
        m[0] = new OSAP("DISNEY WORLD",513,555,w);
        m[2] = new SLC("Finding Nemo",411,555,w); m[17] = new SLC("Finding Nemo",3,198,w); m[33] = new SLC("Finding Nemo",513,198,w);
        m[4] = new Tuition("Wall-E",309,555,w);
        m[7] = new NH("TheInc- redibles",156,555,w); m[22] = new NH("TheInc- redibles",105,45,w);
        m[36] = new NH("TheInc- redibles",513,351,w);
        m[10] = new DCTims("Space Buddies",3,555,w);
        m[20] = new Goose("Monsters Inc",3,45,w);
        m[30] = new GTT("Sent TO Space",513,45,w);
        m[38] = new Coop("Pirates Coming",513,453,w);
        // finish initialization
	} else {
        m[5] = new Rez("MKV",200,25,258,555,258,525,289,525,w);
        m[15] = new Rez("UWP",200,25,3,300,3,270,34,270,w);
        m[25] = new Rez("V1",200,25,258,45,258,15,289,15,w);
        m[35] = new Rez("REV",200,25,513,300,513,270,544,270,w);
    
        // initialize 2 gyms
        m[12] = new Gym("PAC",150,0,3,453,3,423,34,423,w);
        m[28] = new Gym("CIF",150,0,411,45,411,15,442,15,w);
    
        // initialize "Arts1"
        m[1] = new Academic("AL",40,2,"Arts1",50,tuition[0],462,555,462,525,493,525,w);
        m[3] = new Academic("ML",60,4,"Arts1",50,tuition[1],360,555,360,525,391,525,w);
    
        // initialize "Arts2"
        m[6] = new Academic("ECH",100,6,"Arts2",50,tuition[2],207,555,207,525,238,525,w);
        m[8] = new Academic("PAS",100,6,"Arts2",50,tuition[2],105,555,105,525,136,525,w);
        m[9] = new Academic("HH",120,8,"Arts2",50,tuition[3],54,555,54,525,85,525,w);
    
        // initialize "Eng"
        m[11] = new Academic("RCH",140,10,"Eng",100,tuition[4],3,504,3,474,34,474,w);
        m[13] = new Academic("DWE",140,10,"Eng",100,tuition[4],3,402,3,372,34,372,w);
        m[14] = new Academic("CPH",160,12,"Eng",100,tuition[5],3,351,3,321,34,321,w);
    
        // initialize "Health"
        m[16] = new Academic("LHI",180,14,"Health",100,tuition[6],3,249,3,219,34,219,w);
        m[18] = new Academic("BMH",180,14,"Health",100,tuition[6],3,147,3,117,34,117,w);
        m[19] = new Academic("OPT",200,16,"Health",100,tuition[7],3,96,3,66,34,66,w);
    
        // initialize "Env"
        m[21] = new Academic("EV1",220,18,"Env",150,tuition[8],54,45,54,15,85,15,w);
        m[23] = new Academic("EV2",220,18,"Env",150,tuition[8],156,45,156,15,187,15,w);
        m[24] = new Academic("EV3",240,20,"Env",150,tuition[9],207,45,207,15,238,15,w);
    
        // initialize "Sci1"
        m[26] = new Academic("PHYS",260,22,"Sci1",150,tuition[10],309,45,309,15,340,15,w);
        m[27] = new Academic("B1",260,22,"Sci1",150,tuition[10],360,45,360,15,391,15,w);
        m[29] = new Academic("B2",280,24,"Sci1",150,tuition[11],462,45,462,15,493,15,w);
    
        // initialize "Sci2"
        m[31] = new Academic("EIT",300,26,"Sci2",200,tuition[12],513,96,513,66,544,66,w);
        m[32] = new Academic("ESC",300,26,"Sci2",200,tuition[12],513,147,513,117,544,117,w);
        m[34] = new Academic("C2",320,28,"Sci2",200,tuition[13],513,249,513,219,544,219,w);
    
        // initialize "Math"
        m[37] = new Academic("MC",350,35,"Math",200,tuition[14],513,402,513,372,544,372,w);
        m[39] = new Academic("DC",400,50,"Math",200,tuition[15],513,504,513,474,544,474,w);
    
        // initialize all unownable buildings
        m[0] = new OSAP("COLLECT OSAP",513,555,w);
        m[2] = new SLC("SLC",411,555,w); m[17] = new SLC("SLC",3,198,w); m[33] = new SLC("SLC",513,198,w);
        m[4] = new Tuition("TUITION",309,555,w);
        m[7] = new NH("NEEDLES HALL",156,555,w); m[22] = new NH("NEEDLES HALL",105,45,w);
        m[36] = new NH("NEEDLES HALL",513,351,w);
        m[10] = new DCTims("DC Tims Line",3,555,w);
        m[20] = new Goose("Goose Nesting",3,45,w);
        m[30] = new GTT("GO TO TIMS",513,45,w);
        m[38] = new Coop("COOP FEE",513,453,w);
        // finish initialization
    }
    
    // add neighbours now (monopolies & rez & gym)
    m[12]->addNei(m[28]); m[28]->addNei(m[12]);
    m[5]->addNei(m[15]); m[5]->addNei(m[25]); m[5]->addNei(m[35]);
    m[15]->addNei(m[5]); m[15]->addNei(m[25]); m[15]->addNei(m[35]);
    m[25]->addNei(m[5]); m[25]->addNei(m[15]); m[25]->addNei(m[35]);
    m[35]->addNei(m[5]); m[35]->addNei(m[15]); m[35]->addNei(m[25]);
    m[1]->addNei(m[3]); m[3]->addNei(m[1]);
    for (int i=6; i<=21; i+=5) {m[i]->addNei(m[i+2]); m[i]->addNei(m[i+3]);}
    for (int i=8; i<=23; i+=5) {m[i]->addNei(m[i-2]); m[i]->addNei(m[i+1]);}
    for (int i=9; i<=24; i+=5) {m[i]->addNei(m[i-3]); m[i]->addNei(m[i-1]);}
    for (int i=26; i<=31; i+=5) {m[i]->addNei(m[i+1]); m[i]->addNei(m[i+3]);}
    for (int i=27; i<=32; i+=5) {m[i]->addNei(m[i-1]); m[i]->addNei(m[i+2]);}
    for (int i=29; i<=34; i+=5) {m[i]->addNei(m[i-3]); m[i]->addNei(m[i-2]);}
    m[37]->addNei(m[39]); m[39]->addNei(m[37]);
}

Board::~Board() {
    for (int i=0; i<40; i++) { delete m[i]; }
}

Building* Board::pos() { return m[0]; } // access OSAP only // set option to the class

string Board::getName(int index) { return m[index]->getName(); }

bool Board::own(int index) { return m[index]->getOwn(); }

Player *Board::getOwner(int index) { return m[index]->getOwner(); }

int Board::getCost(int index) {return m[index]->getCost();}

bool Board::getMort(int index) {return m[index]->getMort();}

void Board::setOwner(int index, Player *p) {m[index]->setOwner(index,p);}

void Board::improve(int index, std::string s) {m[index]->improve(index, s);}

void Board::changeImprove(int index, int i) {m[index]->changeImprove(index, i);}

bool Board::isMonopoly(int index) {return m[index]->isMonopoly();}

void Board::changeMort(int index, string s) {m[index]->changeMort(index, s);}

int Board::getPay(int index) {return m[index]->getPay();}

int Board::getLevel(int index) {return m[index]->getLevel();}

void Board::auction(int index, vector<Player*>*players, map<string,int>* order, int turn, int numPlayer, bool bankrupt) {m[index]->auction(index,players,order,turn,numPlayer,bankrupt);}

bool Board::checkNei(int index) {return m[index]->checkNei();}

bool Board::change(int index, Player *p) {return m[index]->change(p);}

