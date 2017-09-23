all: bb7kbonus

bb7k: main.o board.o display.o player.o building.o ownable.o academic.o rez.o gym.o unownable.o slc.o coop.o dctims.o goose.o gtt.o nh.o OSAP.o tuition.o
	g++ -DBONUS=no window.cpp ownable.cpp display.cpp main.o board.o player.o building.o academic.o rez.o gym.o unownable.o slc.o coop.o dctims.o goose.o gtt.o nh.o OSAP.o tuition.o -o bb7k -lX11 -L/usr/X11/lib -I/usr/X11/include

bb7kbonus: graphicMain.cpp window.cpp graphicOwnable.cpp graphicDisplay.cpp board.o player.o building.o academiceven.o rez.o gym.o unownable.o slc.o coop.o dctims.o goose.o gtt.o nh.o OSAP.o tuition.o
	g++ -DBONUS=yes graphicMain.cpp window.cpp graphicOwnable.cpp graphicDisplay.cpp board.o player.o building.o academiceven.o rez.o gym.o unownable.o slc.o coop.o dctims.o goose.o gtt.o nh.o OSAP.o tuition.o -o bb7k -lX11 -L/usr/X11/lib -I/usr/X11/include

main.o: main.cpp
	g++ -c main.cpp

board.o: board.cpp
	g++ -c board.cpp

display.o: display.cpp
	g++ -c display.cpp

player.o: player.cpp
	g++ -c player.cpp

building.o: building.cpp
	g++ -c building.cpp

ownable.o: ownable.cpp
	g++ -c ownable.cpp

academic.o: academic.cpp
	g++ -c academic.cpp

rez.o: rez.cpp
	g++ -c rez.cpp

gym.o: gym.cpp
	g++ -c gym.cpp

unownable.o: unownable.cpp
	g++ -c unownable.cpp

slc.o: slc.cpp
	g++ -c slc.cpp

coop.o: coop.cpp
	g++ -c coop.cpp

dctims.o: dctims.cpp
	g++ -c dctims.cpp

goose.o: goose.cpp
	g++ -c goose.cpp

gtt.o: gtt.cpp
	g++ -c gtt.cpp

nh.o: nh.cpp
	g++ -c nh.cpp

OSAP.o: OSAP.cpp
	g++ -c OSAP.cpp

tuition.o:tuition.cpp
	g++ -c tuition.cpp	

graphicMain: graphicMain.cpp
	g++ -c graphicMain.cpp

window.o: window.cpp
	g++ -c window.cpp

graphicDisplay.o: graphicDisplay.cpp
	g++ -c graphicDisplay.cpp

graphicOwnable.o: graphicOwnable.cpp
	g++ -c graphicOwnable.cpp

academiceven.o: academiceven.cpp
	g++ -c academiceven.cpp
