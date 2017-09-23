#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(bool theme, int width, int height): width(width), height(height) {
    
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);
    
    Pixmap pix = XCreatePixmap(d,w,width,
                               height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);
    
    XFlush(d);
    XFlush(d);
    
    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[12][10]={"white", "black", "pink", "#90EE90", "plum", "cyan", "yellow", "#B0E0E6", "orange", "#DCDCDC","#FFE4B5","#FF6347"};
    
    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 12; ++i) {
        if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
            cerr << "Bad colour: " << color_vals[i] << endl;
        }
        if (!XAllocColor(d,cmap,&xcolour)) {
            cerr << "Bad colour: " << color_vals[i] << endl;
        }
        colours[i]=xcolour.pixel;
    }
    
    XSetForeground(d,gc,colours[Black]);
    
    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);
    
    XSynchronize(d,True);
    usleep(2500);
    XSelectInput(d,w,ExposureMask);
    XFlush(d);
    XEvent event;
    XNextEvent(d,&event); //Hang until the window is ready.
    XSelectInput(d,w,0);
    
    // initialize all the coordinates of strings that store players' char
    for (int i=0, j=513; i<=10; i++,j-=51) {
        playerStr[i][0]=j;
        playerStr[i][1]=555;
    }
    for (int i=11, j=504; i<=19; i++,j-=51) {
        playerStr[i][0]=3;
        playerStr[i][1]=j;
    }
    for (int i=20, j=3; i<=30; i++,j+=51) {
        playerStr[i][0]=j;
        playerStr[i][1]=45;
    }
    for (int i=31, j=96; i<=39; i++,j+=51) {
        playerStr[i][0]=513;
        playerStr[i][1]=j;
    }
    
    // set an array to store the colour of every square
    recColours[0]=0;   recColours[1]=5;  recColours[2]=0;  recColours[3]=5;  recColours[4]=0;
    recColours[5]=10;  recColours[6]=4;  recColours[7]=0;  recColours[8]=4;  recColours[9]=4;
    recColours[10]=0;  recColours[11]=7; recColours[12]=9; recColours[13]=7; recColours[14]=7;
    recColours[15]=10; recColours[16]=6; recColours[17]=0; recColours[18]=6; recColours[19]=6;
    recColours[20]=0;  recColours[21]=3; recColours[22]=0; recColours[23]=3; recColours[24]=3;
    recColours[25]=10; recColours[26]=2; recColours[27]=2; recColours[28]=9; recColours[29]=2;
    recColours[30]=0;  recColours[31]=8; recColours[32]=8; recColours[33]=0; recColours[34]=8;
    recColours[35]=10; recColours[36]=0; recColours[37]=11; recColours[38]=0; recColours[39]=11;
    
    fillRectangle(0,0,562,1,1);
    fillRectangle(0,51,562,1,1);
    for (int i = 102; i <= 459; i+=51) {
        fillRectangle(0,i,51,1,1);
        fillRectangle(510,i,51,1,1);
    }
    fillRectangle(0,510,562,1,1);
    fillRectangle(0,561,562,1,1);
    
    fillRectangle(0,0,1,562,1);
    fillRectangle(51,0,1,562,1);
    for (int i = 102; i <= 459; i+=51) {
        fillRectangle(i,0,1,51,1);
        fillRectangle(i,510,1,51,1);
    }
    fillRectangle(510,0,1,562,1);
    fillRectangle(561,0,1,562,1);
    
    fillRectangle(150,230,264,2,1);
    fillRectangle(150,230,2,102,1);
    fillRectangle(150,331,264,2,1);
    fillRectangle(412,230,2,102,1);
    
    
    drawBigString(215,295,"BB7000",1);
    
    // Gym
    fillRectangle(1, 409, 50, 50, 9);
    fillRectangle(409, 1, 50, 50, 9);
    // Rez
    fillRectangle(256, 1, 50, 50, 10);
    fillRectangle(1, 256, 50, 50, 10);
    fillRectangle(511, 256, 50, 50, 10);
    fillRectangle(256, 511, 50, 50, 10);
    // "Env"
    fillRectangle(52, 1, 50, 50, 3);
    fillRectangle(154, 1, 50, 50, 3);
    fillRectangle(205, 1, 50, 50, 3);
    // "Sci1"
    fillRectangle(307, 1, 50, 50, 2);
    fillRectangle(358, 1, 50, 50, 2);
    fillRectangle(460, 1, 50, 50, 2);
    // "Arts2"
    fillRectangle(52, 511, 50, 50, 4);
    fillRectangle(103, 511, 50, 50, 4);
    fillRectangle(205, 511, 50, 50, 4);
    // "Arts1"
    fillRectangle(358, 511, 50, 50, 5);
    fillRectangle(460, 511, 50, 50, 5);
    // "Health"
    fillRectangle(1, 52, 50, 50, 6);
    fillRectangle(1, 103, 50, 50, 6);
    fillRectangle(1, 205, 50, 50, 6);
    // "Eng"
    fillRectangle(1, 307, 50, 50, 7);
    fillRectangle(1, 358, 50, 50, 7);
    fillRectangle(1, 460, 50, 50, 7);
    // "Sci2"
    fillRectangle(511, 52, 50, 50, 8);
    fillRectangle(511, 103, 50, 50, 8);
    fillRectangle(511, 205, 50, 50, 8);
    // "Math"
    fillRectangle(511, 358, 50, 50, 11);
    fillRectangle(511, 460, 50, 50, 11);

    if (theme) {
        drawString(3,15,"Monsters");
        drawString(3,27,"Inc");
    
        drawString(3,168,"Finding");
        drawString(3,180,"Nemo");
        
        drawString(411,525,"Finding");
        drawString(411,537,"Nemo");
        
        drawString(513,168,"Finding");
        drawString(513,180,"Nemo");
    
        drawString(3,282,"Bambi");
    
        drawString(3,435,"Pooh");
    
        drawString(3,525,"Space");
        drawString(3,537,"Buddies");
    
        drawString(156,525,"The Inc-");
        drawString(156,537,"redibles");
    
        drawString(258,537,"Dumbo");
    
        drawString(309,525,"Wall-E");
    
        drawString(156,525,"The Inc-");
        drawString(156,537,"redibles");
    
        drawString(258,27,"ToyStory");
    
        drawString(411,27,"Popeye");
    
        drawString(513,15,"Sent To");
        drawString(513,27,"Space");
        drawString(513,282,"Tangled");
    
        drawString(156,525,"The Inc-");
        drawString(156,537,"redibles");
        
        drawString(105,15,"The Inc-");
        drawString(105,27,"redibles");
        
        drawString(513,321,"The Inc-");
        drawString(513,333,"redibles");
    
        drawString(513,423,"Pirates");
        drawString(513,435,"Coming");
    
        drawString(513,525,"DISNEY");
        drawString(513,537,"WORLD");
        drawString(54,28,"Atlantis");    fillRectangle(51,17,51,1,1);
        drawString(156,28,"Caribean");
        drawString(207,28,"Frozen");   fillRectangle(153,17,102,1,1);
        drawString(309,28,"Miracle");
        drawString(360,28,"LionKing");    fillRectangle(306,17,102,1,1);
        drawString(462,28,"Valiant");    fillRectangle(459,17,51,1,1);
    
        drawString(54,538,"Genius");
        drawString(105,538,"Oz");  fillRectangle(51,527,102,1,1);
        drawString(207,538,"Mulan");  fillRectangle(204,527,51,1,1);
        drawString(360,538,"Up");   fillRectangle(357,527,51,1,1);
        drawString(462,538,"TRON");   fillRectangle(459,527,51,1,1);
    
        drawString(3,79,"Holes");     fillRectangle(0,68,51,1,1);
        drawString(3,130,"SnowDogs");    fillRectangle(0,119,51,1,1);
        drawString(3,232,"Brave");    fillRectangle(0,221,51,1,1);
        drawString(3,334,"Dinosaur");    fillRectangle(0,323,51,1,1);
        drawString(3,385,"AirBud");    fillRectangle(0,374,51,1,1);
        drawString(3,487,"PeterPan");    fillRectangle(0,476,51,1,1);
    
        drawString(513,79,"TheWild");   fillRectangle(510,68,51,1,1);
        drawString(513,130,"Underdog");  fillRectangle(510,119,51,1,1);
        drawString(513,232,"Bolt");   fillRectangle(510,221,51,1,1);
        drawString(513,385,"Cars");   fillRectangle(510,374,51,1,1);
        drawString(513,487,"Planes");   fillRectangle(510,476,51,1,1);
        
    } else {
        drawString(3,15,"Goose");
        drawString(3,27,"Nesting");
        
        drawString(3,168,"SLC");
        
        drawString(3,282,"UWP");
        
        drawString(3,435,"PAC");
        
        drawString(3,525,"DC Tims");
        drawString(3,537,"Line");
        
        drawString(156,525,"NEEDLES");
        drawString(156,537,"HALL");
        
        drawString(258,537,"MKV");
        
        drawString(309,525,"TUITION");
        
        drawString(411,525,"SLC");
        
        drawString(105,15,"NEEDLES");
        drawString(105,27,"HALL");
        
        drawString(258,27,"V1");
        
        drawString(411,27,"CIF");
        
        drawString(513,15,"GO TO");
        drawString(513,27,"TIMS");
        
        drawString(513,168,"SLC");
        
        drawString(513,282,"REV");
        
        drawString(513,321,"NEEDLES");
        drawString(513,333,"HALL");
        
        drawString(513,423,"COOP");
        drawString(513,435,"FEE");
        
        drawString(513,525,"COLLECT");
        drawString(513,537,"OSAP");
        
        drawString(54,28,"EV1");    fillRectangle(51,17,51,1,1);
        drawString(156,28,"EV2");
        drawString(207,28,"EV3");   fillRectangle(153,17,102,1,1);
        
        drawString(309,28,"PHYS");
        drawString(360,28,"B1");    fillRectangle(306,17,102,1,1);
        drawString(462,28,"B2");    fillRectangle(459,17,51,1,1);
        
        drawString(54,538,"HH");
        drawString(105,538,"PAS");  fillRectangle(51,527,102,1,1);
        drawString(207,538,"ECH");  fillRectangle(204,527,51,1,1);
        
        drawString(360,538,"ML");   fillRectangle(357,527,51,1,1);
        drawString(462,538,"AL");   fillRectangle(459,527,51,1,1);
        
        drawString(3,79,"OPT");     fillRectangle(0,68,51,1,1);
        drawString(3,130,"BMH");    fillRectangle(0,119,51,1,1);
        drawString(3,232,"LHI");    fillRectangle(0,221,51,1,1);
        
        drawString(3,334,"CPH");    fillRectangle(0,323,51,1,1);
        drawString(3,385,"DWE");    fillRectangle(0,374,51,1,1);
        drawString(3,487,"RCH");    fillRectangle(0,476,51,1,1);
        
        drawString(513,79,"EIT");   fillRectangle(510,68,51,1,1);
        drawString(513,130,"ESC");  fillRectangle(510,119,51,1,1);
        drawString(513,232,"C2");   fillRectangle(510,221,51,1,1);
        
        drawString(513,385,"MC");   fillRectangle(510,374,51,1,1);
        drawString(513,487,"DC");   fillRectangle(510,476,51,1,1);
    }
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

int Xwindow::getPX(int position) { return playerStr[position][0]; }
int Xwindow::getPY(int position) { return playerStr[position][1]; }
int Xwindow::getColour(int position) { return recColours[position]; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    Font f = XLoadFont(d, "6x13");
    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}


void Xwindow::drawBigString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    
    
    //set default font
    Font f = XLoadFont(d, "9x15bold");
    
    
    // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
    ostringstream name;
    name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";
    
    XFontStruct * fStruct = XLoadQueryFont(d, name.str().c_str());
    
    if (fStruct) { //font was found, replace default
        f = fStruct->fid;
    }
    
    
    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    //  ti.font = f->fid;
    ti.font = f;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}

void Xwindow::showAvailableFonts() {
    int count;
    char** fnts = XListFonts(d, "*", 10000, &count);
    
    for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}
