/*
 *	Carz
 *	Alexander Shmakov
 *	v 2.0
 */

/* 
#| ___       |#
#| OAO       |#
#|  H        |#
#| OUO       |#
#|           |#
#|           |#
#|           |#
#|       ___ |#
#|       OAO |#
#|        H  |#
#|       OUO |#
#|           |#
#|           |#
#|    ___    |#
#|    OAO    |#
#| <-  H  -> |#
#|    OUO    |#
#^^^^^^^^^^^^^#
*/
 
#include <iostream>
using namespace std;

#include <ncurses.h>
#include <ctime>
#include <stdlib.h>
#include "carz.h"

int main () {

	//set seed to NULL
	srand (time(NULL));
	
	int count = 0;
	bool end = false;
	
	//configuring ncurses
	initscr();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	
	//printing instructions
	mvprintw(0, 0, "Welcome to \"Carz\" \nPress the arrow keys (<- or ->) to avoid the other cars \n\nPress any key to start\n\n");
	refresh();
	
	//press anything to start
	cin.ignore();
	
	mvprintw(0, 0, "                                                                                                            \n\n                       ");
	refresh();
	mvprintw(3, 40, " ____________________________________" );
	mvprintw(4, 40, "|                                    |");
	mvprintw(5, 40, "| #####     ###     ####    ######## |");
	mvprintw(6, 40, "| ##       ## ##    ##  #      ###   |");
	mvprintw(7, 40, "| ##      #######   #####    ###     |");
	mvprintw(8, 40, "| #####  ##     ##  ##  ##  ######## |");
	mvprintw(9, 40, "|____________________________________|");
	mvprintw(10, 41, "    Made by: Alexander S");
	refresh();

	//GAME STARTS
	play(count);
	gameOver();
		
	endwin();

	return 0;
}
