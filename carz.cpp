/*
 *	Carz
 *	Alexander S
 *	v 2.0
 */
 
#include <iostream>
using namespace std;

#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include "carz.h"


void playGameIntro() {

	//prints the road
	printTrack(trackLength);
	
	//animation leading to start
	for (int i = 0; i < startTime; i++) {
		
		curs_set(0);

		if(i>0) {		
			mvprintw(i-1, 0, "#|           |#");
			refresh();
		}
		
		mvprintw(i,   6, "___");
		refresh();
		mvprintw(i+1, 6, "OAO");
		refresh();
		mvprintw(i+2, 6, " H ");
		refresh();
		mvprintw(i+3, 6, "OUO");
		refresh();	
		usleep(sleepTime/2);
	}	
	
	//animation to display start/finish line	
	startFinish(done);	
	return;
}

//prints the margins of the game screen
void printTrack(int length) {

	for (int i = 0; i < length; i++) {
	
		curs_set(0);
		if(i !=	25) {
			
			if(i>0) {
				mvprintw(i-1, 0, "#|           |#");
				refresh();
				mvprintw(i-1, 0, "#|           |#");
				refresh();
			}
			mvprintw(i, 0, "#|           |#");	
			refresh();
		}
		else {
			mvprintw(25, 0, "#^^^^^^^^^^^^^#");	
			refresh();
		}

		usleep(sleepTime/3);
	}
	return;
}

void printCars(int side, int& count, bool& lost) {
	
	curs_set(0);
	int pos;
	int playerMove; 

	//decides on which side to print another car
	if (side == 0) {
		pos = 4;
	}
	else if(side == 1) {
		pos = 8;
	}
	else {
		pos = 6;
	}
	
	for (int i = 0; i < trackLength; i++) {

		//removes remainings of previous prints
		if(i>0) {

			mvprintw(i-1, pos, "   ");
			refresh();
		}
		
		//decides if game over
		if(i >= 19) {
			
			//cases when collision detected
			if(pos==4 && x<=6 ) {														
				lost = true;
				break;
			}	
			else if(pos==6 && x>=4 && x<=8) {
				lost = true;
				break;
			}
			else if(pos==8 && x>=6) {	
				lost = true;
				break;
			}	
		}	
		
		//	removes remainings of previous prints	
		if(i == trackLength-1) {
			
			mvprintw(i,   pos, "^^^");
			refresh();
			mvprintw(i+1, pos, "   ");
			refresh();
			mvprintw(i+2, pos, "   ");
			refresh();
			mvprintw(i+3, pos, "   ");
			refresh();	
			usleep(sleepTime/3);
		}
		//the animation of a car you are overtaking
		else {
			
			mvprintw(i,   pos, "___");
			refresh();
			mvprintw(i+1, pos, "OAO");
			refresh();
			mvprintw(i+2, pos, " H ");
			refresh();
			mvprintw(i+3, pos, "OUO");
			refresh();

			//speed control	
			usleep(sleepTime *genSpeed());	
				
			playerMove = getChar(Nomove); 
			move( playerMove );
		}		
	}//for i
	
	if(lost == true){
		return;
	}
	
	count++;
	
	// amount of cars you willover take in the game 
	if (count < totalCars) {
		return printCars( genSide(), count, lost);
	}
	//animation of approaching finish line
	else {
		startFinish(done);
	}
	
	return;	
}


//generates on which position to place another car
int genSide() {
	int num = rand() %3;
	return num;
}

//printing the start or finish line if the race is finished
void startFinish(bool& done) {

	for (int i = 0; i < startTime-1; i++) {

		curs_set(0);

		if(i>0) {
			mvprintw(i-1, 0, "#|           |#");
			refresh();
		}
	
		if(!done) {
			mvprintw(i, 0, "#|## START ##|#");
			refresh();	
			usleep(sleepTime/2);				
		}
		else{
			mvprintw(i, 0, "#|# FINISH ##|#");
			refresh();		
			usleep(sleepTime);		
		}		
	}//for i
		
	mvprintw(20, 0, "#|           |#");	
	refresh();
	done = true;
	return;	
}

//updating the location on the user's car after key press
void move(int move) {

	if(move == 0) {
		return;
	}

	int y = startTime-1;
		
	switch(move) {
	
		case KEY_LEFT:
		
			if(x>2)
				x = x-2;
		
			curs_set(0);
		
			mvprintw(y,     x, "___");
			mvprintw(y,   x+3, "  ");
			refresh();
			mvprintw(y+1,   x, "OAO");
			mvprintw(y+1, x+3, "  ");
			refresh();
			mvprintw(y+2,   x, " H ");
			mvprintw(y+2, x+3, "  ");
			refresh();
			mvprintw(y+3,   x, "OUO");
			mvprintw(y+3, x+3, "  ");
			refresh();	
			break;
		
		case KEY_RIGHT:
		
			if(x<10)
				x = x+2;
		
			curs_set(0);
		
			mvprintw(y,     x, "___");
			mvprintw(y,   x-2, "  ");
			refresh();
			mvprintw(y+1,   x, "OAO");
			mvprintw(y+1, x-2, "  ");
			refresh();
			mvprintw(y+2,   x, " H ");
			mvprintw(y+2, x-2, "  ");
			refresh();
			mvprintw(y+3,   x, "OUO");
			mvprintw(y+3, x-2, "  ");			
			refresh();		
			break;
	}
	
	return;
}

//returns the key that the user chose as their input
int getChar(int defaultCh) {

	nodelay(stdscr, true);
    int tmp = getch();
    if(tmp != defaultCh) {
    	return tmp;
    }
    else {
    	return defaultCh;
    }
}

//print the YOU WON, or GAME OVER screen
void gameOver() {

	curs_set(0);
	
	if(lost) {
		for (int i = 0; i < trackLength-2; i++) {
			if(i>0) {
				mvprintw(i-1, 0, "#|           |#");
				refresh();
			}

			mvprintw(i,   0, "#| GAME ^^^^ |#");
			mvprintw(i+1, 0, "#| ^^^^ OVER |#");
			refresh();	
			usleep(sleepTime/2);				
		}// for i
	}
	
	for (int i = 0; i < trackLength+4; i++) {		
		mvprintw(i, 0, "                                 ");
	}
	
	refresh();
	
	if(lost == false) {
		mvprintw(4, 2, "YOU WON!");
		refresh();
		usleep(sleepTime*5);
	}	
	else{
		mvprintw(4, 2, "GAME OVER!");
		refresh();
		usleep(sleepTime*5);
	}
	
	mvprintw(4, 2, "                              ");
	refresh();
	
	return;
}

//generated random speeds at which the other cars will apptoach you
double genSpeed() {
	double num = rand() %2;	
	if(num < 0.3) {
		num += 0.2;
	}
	else if(num > 0.3 && num < 0.65) {
		num += 0.2;
	}
	else if(num > 0.65) {
		num -= 0.25;	
	}
	return num;
}

//initiates the start of the game
void play(int count) {
	playGameIntro();
	printCars(genSide(), count, lost);
	return;
}	
