#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>
class Xwindow;

struct Coordinate {
    int f,s; // f:first & s:second
};

class TextDisplay {
    Xwindow *w;
    std::string board[23][56];
    std::map<std::string,int> players; //recording the position of every player;
    int playerStr[40][2];//recording the coordinates of strings that store players' char
    std::map<int,Coordinate> improveStr;//recording the coordinates of strings that store a number of I's
public:
    TextDisplay(bool theme, Xwindow *w=NULL);
    void addPlayer(std::string s);
    void changePosition(std::string s, int position);
    void improve(int level, int position, int ix, int iy);
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif