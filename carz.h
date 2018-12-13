/*
 *	Carz
 *	Alexander Shmakov
 *	v 2.0
 */


//global values
static int totalCars = 25; // the more cars passed the faster the game 

static const int startTime = 22;     
static const int trackLength = 26;
static const unsigned long sleepTime = 100000; 
static bool lost = false;
static bool done = false;
static const int Nomove = 0;
static int x = 6;

void playGameIntro();
void gameOver();
void printCars(int, int&, bool&);
void printTrack(int);
void startFinish(bool&);
void move(int);
void play(int);
double genSpeed();
int getChar(int);
int genSide();
