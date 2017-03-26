//Headers
#include <iostream>
#include <string> 
#include <stdlib.h> 

using namespace std;

static char board[20][20]; //The Board

//Player defining class
class Player {
	private: //Player data
		int posX;
		int posY;

	public:  //Player getters/setters/functions
		int getPosX () {
			return posX;
		}
		int getPosY () {
			return posY;
		}

		void setPosX (int x) {
			posX = x;
		}
		void setPosY (int y) {
			posY = y;
		}

		void moveX (int amountX) {
				board[posY][posX] = '.';
				posX += amountX;
		}

		void moveY (int amountY) {
				board[posY][posX] = '.';
				posY += amountY;
		}
};

class Enemy {
	private: //Enemy data
		int posX;
		int posY;

	public:  //Enemy getters/setters/functions
		int getPosX () {
			return posX;
		}
		int getPosY () {
			return posY;
		}

		void setPosX (int x) {
			posX = x;
		}
		void setPosY (int y) {
			posY = y;
		}

		void moveX (int amountX) {
			if (amountX < 0 && posX == 0 || amountX > 0 && posX == 19) {
			} else {
				board[posY][posX] = '.';
				posX += amountX;
			}
		}

		void moveY (int amountY) {
			if (amountY < 0 && posY == 0 || amountY > 0 && posY == 19) {
			} else {
				board[posY][posX] = '.';
				posY += amountY;
			}
		}
};


//Random generator
int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if ( first ) 
   {  
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}

Player plr; //Player object

//Board init
void start () {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			board[i][j] = '.';
		}
	}

	plr.setPosX(1);
	plr.setPosY(18);
}

void moveEnemy (Enemy enm[], int count) { //Enemy movement handler
	for (int i = 0; i < count; i++) { 
		int mode = random(0, 5);
		switch (mode) { //Direction check
			case 1:
				enm[i].moveY(-1); //up
				break;
			case 2:
				enm[i].moveX(1); //right
				break;
			case 3:
				enm[i].moveY(1); //down
				break;
			case 4:
				enm[i].moveX(-1); //left
				break;
			default: //null
				break;
		}
	}
}

//Board updater
void updateBoard (Player p, Enemy en[], int count) {
	board[p.getPosY()][p.getPosX()] = 'P';

	for (int i = 0; i < count; i++) { //Enemy init
		board[en[i].getPosY()][en[i].getPosX()] = 'E';
	}
}

//Board printer
void printBoard() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			cout << board[i][j] << "   ";
		}
		cout << endl;
	}
}


//Main Procces
int main()
{
	bool dead = false;  //Player state
	bool won = false; //Win state

	string str;  //Input
	char input;

	int enemyCount = random(2, 7); //Enemy count and object
	Enemy enm[enemyCount];

	for (int i = 0; i < enemyCount; i++) { //Enemy init
		enm[i].setPosX(random(0,19));
		enm[i].setPosY(random(0,19));
	}

	start();
	while (dead != true || won != false) {
		moveEnemy(enm, enemyCount); //Call of the enemy movement

		updateBoard(plr, enm, enemyCount); //Updating
		printBoard();	//Printing the board
		cout << endl;

		for (int i = 0; i < enemyCount; i++) { //Enemy kill check
			if (plr.getPosX() == enm[i].getPosX() && plr.getPosY() == enm[i].getPosY()) {
				cout << endl << "You are dead :(" << endl;
				dead = true;
			}
		}

		cout << endl;		//Player input handler
		cin >> str;
		input = str.at(0);
		cout << endl;
		

		switch (input) { //Player input handler
			case 'd': 
				if (plr.getPosX() == 19) {
					cout << "you suck" << endl << endl;
					break;
				} else {
					plr.moveX(1);
					break;
				}
			case 'a': 	
				if (plr.getPosX() == 0) {
					cout << "You are hitting the cold walls of the dungeon..." << endl << endl;
					break;
				} else {
					plr.moveX(-1);
					break;
				}
			case 'w': 	
				if (plr.getPosY() == 0) {
					cout << "You are hitting the cold walls of the dungeon..." << endl << endl;
					break;
				} else {
					plr.moveY(-1);
					break;
				}
			case 's': 	
				if (plr.getPosY() == 19) {
					cout << "You are hitting the cold walls of the dungeon..." << endl << endl;
					break;
				} else {
					plr.moveY(1);
					break;
				}
			case 'q':
				cout << "You are dead :(";
				dead = true;
				break;
			default:
				cout << "What is that??" << endl;
				break;
		}

		for (int i = 0; i < enemyCount; i++) { //Enemy kill check
			if (plr.getPosX() == enm[i].getPosX() && plr.getPosY() == enm[i].getPosY()) {
				updateBoard(plr, enm, enemyCount); //Updating
				printBoard();	//Printing the board
				cout << endl << "You are dead :(" << endl;
				dead = true;
			}
		}


	}
	
    return 0;
}
