#include "display.h"
using namespace std;

TextDisplay::TextDisplay(bool theme, Xwindow *w): w(w) {
    // initialize every string to empty
    for (int i=0; i<23; i++) {
        for (int j=0; j<56; j++) { board[i][j]=""; }
    }
    
    // initialize the boundaries
    for (int i=0; i<23; i+=2) { board[i][0]="_"; }
    for (int i=4; i<=18; i+=2) { board[i][50]="_"; }
    for (int i=1; i<23; i+=2) { board[i][0]="________"; }
    for (int i=1; i<23; i+=2) { board[i][5]="________"; }
    for (int i=1; i<23; i+=2) { board[i][50]="________"; }
    for (int i=1; i<23; i+=2) { board[i][55]="________"; }
    for (int i=0; i<23; i+=2) {
        for (int j=1; j<=5; j++) { board[i][j]="|"; }
    }
    for (int i=0; i<23; i+=2) {
        for (int j=51; j<=55; j++) { board[i][j]="|"; }
    }
    for (int i=6; i<=50; i++) { board[0][i]="|"; }
    for (int i=6; i<=50; i++) { board[2][i]="|"; }
    for (int i=6; i<=50; i++) { board[20][i]="|"; }
    for (int i=6; i<=50; i++) { board[22][i]="|"; }
    for (int i=10; i<=45; i+=5) {
        board[1][i]="________"; board[21][i]="________";
    }
    board[3][2]="--------"; board[7][2]="--------"; board[9][2]="--------";
    board[13][2]="--------"; board[15][2]="--------"; board[19][2]="--------";
    board[1][7]="--------"; board[1][12]="--------"; board[1][22]="--------";
    board[1][32]="--------"; board[1][37]="--------"; board[1][47]="--------";
    board[21][7]="--------"; board[21][12]="--------"; board[21][22]="--------";
    board[21][37]="--------"; board[21][47]="--------";
    board[3][52]="--------"; board[5][52]="--------"; board[9][52]="--------";
    board[15][52]="--------"; board[19][52]="--------";
    
    // initialize all buildings
    if (theme) {
        board[1][1] = "Monsters"; board[1][2] = "Inc     "; board[1][8] = "Holes   ";
        board[1][13]= "SnowDogs"; board[1][16]= "Finding "; board[1][17]= "Nemo    ";
        board[1][23]= "Brave   ";
        board[1][27]= "Bambi   "; board[1][33]= "Dinosaur"; board[1][38]= "AirBud  ";
        board[1][42]= "Pooh    "; board[1][48]= "PeterPan"; board[1][51]= "Space   ";
        board[1][52]= "Buddies "; board[3][3] = "Atlantis"; board[3][53]= "Genius  ";
        board[5][1] = "TheInc- "; board[5][2] = "redibles"; board[5][53]= "Oz      ";
        board[7][3] = "Caribean"; board[7][51] ="TheInc- "; board[7][52]= "redibles";
        board[9][3] = "Frozen  "; board[9][53] ="Mulan   "; board[11][2]= "ToyStory";
        board[11][52]="Dumbo   "; board[13][3] ="Miracle "; board[13][51]="Wall-E  ";
        board[15][3] ="LionKing"; board[15][53]="Up      "; board[17][2]= "Popeye  ";
        board[17][51]="Finding "; board[17][52]="Nemo    "; board[19][3]= "Valiant ";
        board[19][53]="TRON    ";
        board[21][1] ="Sent To "; board[21][2] ="Space   "; board[21][8]= "TheWild ";
        board[21][13]="Underdog"; board[21][16]="Finding "; board[21][17]="Nemo    ";
        board[21][23]="Bolt    ";
        board[21][27]="Tangled "; board[21][31]="TheInc- "; board[21][32]="redibles";
        board[21][38]="Cars    "; board[21][41]="Pirates "; board[21][42]="Coming  ";
        board[21][48]="Planes  "; board[21][51]="DISNEY  "; board[21][52]="WORLD   ";
    } else {
        board[1][1] = "Goose   "; board[1][2] = "Nesting "; board[1][8] = "OPT     ";
        board[1][13]= "BMH     "; board[1][16] ="SLC     "; board[1][23] ="LHI     ";
        board[1][27]= "UWP     "; board[1][33] ="CPH     "; board[1][38] ="DWE     ";
        board[1][42]= "PAC     "; board[1][48] ="RCH     "; board[1][51] ="DC Tims ";
        board[1][52]= "Line    "; board[3][3] = "EV1     "; board[3][53] ="HH      ";
        board[5][1] = "NEEDLES "; board[5][2] = "HALL    "; board[5][53] ="PAS     ";
        board[7][3] = "EV2     "; board[7][51] ="NEEDLES "; board[7][52] ="HALL    ";
        board[9][3] = "EV3     "; board[9][53] ="ECH     "; board[11][2] ="V1      ";
        board[11][52]="MKV     "; board[13][3] ="PHYS    "; board[13][51]="TUITION ";
        board[15][3] ="B1      "; board[15][53]="ML      "; board[17][2] ="CIF     ";
        board[17][51]="SLC     "; board[19][3] ="B2      "; board[19][53]="AL      ";
        board[21][1] ="GO TO   "; board[21][2] ="TIMS    "; board[21][8] ="EIT     ";
        board[21][13]="ESC     "; board[21][16]="SLC     "; board[21][23]="C2      ";
        board[21][27]="REV     "; board[21][31]="NEEDLES "; board[21][32]="HALL    ";
        board[21][38]="MC      "; board[21][41]="COOP    "; board[21][42]="FEE     ";
        board[21][48]="DC      "; board[21][51]="COLLECT "; board[21][52]="OSAP    ";
    }
    
    // initialize the middle "BB7000"
    for (int i=6; i<=16; i+=2) {board[i][24]="_";}
    for (int i=8; i<=14; i+=2) {board[i][31]="_";}
    for (int i=25; i<=31; i++) {board[6][i]="|"; board[16][i]="|";}
    for (int i=7; i<=15; i+=2) {board[i][24]="________"; board[i][31]="________";}
    board[7][26]="  ###   "; board[9][26]="###    #"; board[10][26]="#";
    board[11][26]="###   ##"; board[12][26]="#"; board[13][26]="    ### ";
    board[15][26]="  ###   ";
    board[7][27]="  #  #  "; board[9][27]="#  #    "; board[11][27]=" #   #  ";
    board[13][27]="#  #   #"; board[15][27]=" #   #  ";
    board[7][28]="  ####  "; board[9][28]="####    "; board[11][28]="#    #  ";
    board[13][28]="#  #   #"; board[15][28]=" #   #  ";
    board[7][29]="  #   # "; board[9][29]="#   #   "; board[10][29]="#";
    board[11][29]="     #  "; board[13][29]="#  #   #"; board[15][29]=" #   #  ";
    board[7][30]="  ####  "; board[9][30]="####   #"; board[11][30]="      ##";
    board[12][30]="#"; board[13][30]="    ### "; board[15][30]="  ###   ";
    
    // initialize the remaining strings to be full of whitespaces
    for (int i=4; i<=18; i+=2) {
        for (int j=6; j<=49; j++) {
            if (board[i][j]=="") {board[i][j]=" ";}
        }
    }
    for (int i=0; i<23; i++) {
        for (int j=0; j<56; j++) {
            if (board[i][j]=="") board[i][j]="        "; }
    }
    
    // initialize all the coordinates of strings that store players' char
    for (int i=0, j=21; i<=10; i++,j-=2) {
        playerStr[i][0]=j;
        playerStr[i][1]=54;
    }
    for (int i=11, j=49; i<=19; i++,j-=5) {
        playerStr[i][0]=1;
        playerStr[i][1]=j;
    }
    for (int i=20, j=1; i<=30; i++,j+=2) {
        playerStr[i][0]=j;
        playerStr[i][1]=4;
    }
    for (int i=31, j=9; i<=39; i++,j+=5) {
        playerStr[i][0]=21;
        playerStr[i][1]=j;
    }
    
    // initialize all the coordinates of 22 strings that store a number of I's or M (mortgage)
    improveStr[1].f=19; improveStr[1].s=51;
    improveStr[3].f=15; improveStr[3].s=51;
    improveStr[6].f=9;  improveStr[6].s=51;
    improveStr[8].f=5;  improveStr[8].s=51;
    improveStr[9].f=3;  improveStr[9].s=51;
    improveStr[11].f=1; improveStr[11].s=46;
    improveStr[13].f=1; improveStr[13].s=36;
    improveStr[14].f=1; improveStr[14].s=31;
    improveStr[16].f=1; improveStr[16].s=21;
    improveStr[18].f=1; improveStr[18].s=11;
    improveStr[19].f=1; improveStr[19].s=6;
    improveStr[21].f=3; improveStr[21].s=1;
    improveStr[23].f=7; improveStr[23].s=1;
    improveStr[24].f=9; improveStr[24].s=1;
    improveStr[26].f=13;improveStr[26].s=1;
    improveStr[27].f=15;improveStr[27].s=1;
    improveStr[29].f=19;improveStr[29].s=1;
    improveStr[31].f=21;improveStr[31].s=6;
    improveStr[32].f=21;improveStr[32].s=11;
    improveStr[34].f=21;improveStr[34].s=21;
    improveStr[37].f=21;improveStr[37].s=36;
    improveStr[39].f=21;improveStr[39].s=46;
    
    // initialize the coordinates of strings where Rez and Gym store M (mortgage)
    improveStr[5].f=11; improveStr[5].s=51;   // MKV
    improveStr[12].f=1; improveStr[12].s=41;  // PAC
    improveStr[15].f=1; improveStr[15].s=26;  // UWP
    improveStr[25].f=11;improveStr[25].s=1;   // V1
    improveStr[28].f=17;improveStr[28].s=1;   // CIF
    improveStr[35].f=21;improveStr[35].s=26;  // REV
}

void TextDisplay::addPlayer(string s) {
    for (int i=0; i<8; i++) {
        if (board[21][54][i]==' ') {
            board[21][54].replace(i, 1, s); // add a new player to position 0 OSAP
            break;
        }
    }
    players[s]=0;
}

void TextDisplay::changePosition(string s, int position) {
    int prev = players[s];
    players[s] = position;
    
    // erase player's char from previous position
    string str = board[playerStr[prev][0]][playerStr[prev][1]];
    for (int i=0; i<8; i++) {
        if (str[i]==s[0]) {
            board[playerStr[prev][0]][playerStr[prev][1]]=
            str.substr(0,i)+str.substr(i+1)+" ";
            break;
        }
    }

    // add player's char to his/her current position
    str = board[playerStr[position][0]][playerStr[position][1]];
    for (int i=0; i<8; i++) {
        if (str[i]==' ') {
            board[playerStr[position][0]][playerStr[position][1]]=
            str.substr(0,i)+s+str.substr(i+1);
            break;
        }
    }
}

// change the number of I's at position according to new level
void TextDisplay::improve(int level, int position, int ix, int iy) {
    if (level==-1) {
        board[improveStr[position].f][improveStr[position].s] = "[M]     ";
    } else {
        string i (level,'I');
        string space (8-level,' ');
        board[improveStr[position].f][improveStr[position].s] = i+space;
    }
}

TextDisplay::~TextDisplay() {};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i=0; i<56; i++) {
        for (int j=0; j<23; j++) {
            out << td.board[j][i];
        }
        out << endl;
    }
    return out;
}




