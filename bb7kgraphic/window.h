#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[12];
    int width, height;
    int playerStr[40][2];
    // set an array to store the colour of every square
    int recColours[40];
    
public:
    Xwindow(bool theme=false, int width=562, int height=562);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.
    
    enum {White=0, Black, Pink, LightGreen, Plum, Cyan, Yellow, PowderBlue, Orange, Gainsboro, Moccasin, Tomato}; // Available colours.
    
    int getPX(int position);
    int getPY(int position);
    int getColour(int position);
    
    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);
    
    // Draws a string
    void drawString(int x, int y, std::string msg, int colour=Black);
    
    // Draws a string
    void drawBigString(int x, int y, std::string msg, int colour=Black);
    
    // Prints the first 10000 available fonts
    void showAvailableFonts();
};

#endif
