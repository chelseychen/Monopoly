#include "unownable.h"
#include <string>
using namespace std;

bool Unownable::op1=false;

bool Unownable::op2=false;

bool Unownable::op3=false;

int Unownable::collect=0;

Unownable::Unownable(string name,int px,int py, Xwindow *w): Building(name, false, px, py,w) {}

void Unownable::setOp(bool option1, bool option2, bool option3) {
    op1=option1;
    op2=option2;
    op3=option3;
}

void Unownable::setCollect(int n) {
    if (op2) {
        if (n < 0) {
            cout << ">> Geese left all the money collected so far!! You picked it up, lucky you!!!!! XD" << endl;
            cout << ">> You got $" << collect << "." << endl;
        } else {
            cout << "====<< Money was collected, so the University took back $500 >>====" << endl;
        }
        collect=0;
        op2=false;
    }
    if (n > 0) {
        cout << "[$" << n << " goes to the center.]" << endl;
        collect += n;
    } else if (n < 0) {
        if (collect) {
            cout << ">> Geese left all the money collected so far!! You picked it up, lucky you!!!!! XD" << endl;
            cout << ">> You got $" << collect << "." << endl;
            collect = 0;
        }
    }
}

int Unownable::getcollect() { return collect; }

bool Unownable::getOp2() { return op2; }

Unownable::~Unownable() {}
