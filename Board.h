#ifndef BOARD
#define BOARD

#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>



bool endGame = false, checkFire = false;
int xF, yF, fire = 0;
std::string tellPlayer = "";

class Board {
protected:	
	std::string board[10][10];
	std::string playerBoard = "";
	std::string _team;
	std::string direction, test_X, test_Y;
	int shipSize = 1, x, y, hitCount = 0;
	std::string _fireX, _fireY;											//defines some local variables to the function that are used to store user inputs to be converted to integers

public:
	void initializeGrid() {																													//Function adds a space to each array coordinate to make the board square
		for (int n = 0; n < 10; n++) {
			for (int m = 0; m < 10; m++) {
				board[n][m] = " "; 
			}
		}
	}
	void createBattleGrid() {																												//When called this function will display the players board with a break between each cell of the array
		if (_team == "") { playerBoard = "Player"; }
		else { playerBoard = "Computer"; }
		std::cout << playerBoard << " board	\n" << std::endl << "   0 1 2 3 4 5 6 7 8 9\n" << "   -------------------\n";							//This is also used for coordinate marks for user reference
		for (int n = 0; n < 10; n++) {
			std::cout << n << " |";
			for (int m = 0; m < 10; m++) {
				std::cout << board[n][m] << "|";
			} std::cout << std::endl;
		} std::cout << std::endl;
	}
	void getTarget() {
		while (checkFire == false ) {
			fireCoord();
			if (board[yF][xF] == "X") {
				std::cout << "You have already fired and hit a target at this location. Please enter a new firing solution" << std::endl << std::endl;
				checkFire = false;
			}
			if (board[yF][xF] == "O") {
				std::cout << "You have already fired and missed your target at this location. Please enter a new firing solution" << std::endl << std::endl;
				checkFire = false;
			}
			if (board[yF][xF] == " ") {								//If the array does not hold a ship ("S") than the following condition statement is run prompting the user and updating the boards
				tellPlayer = "You have missed the target, better luck next time\n";
				fire = 1; checkFire = true; board[yF][xF] = "O";
			}
			if (board[yF][xF] == "S") {								//If the array does hold a ship ("S") than the following condition statement is run prompting the user and updating the boards and adding to the players hitcount
				tellPlayer = "Congratulations, you have hit an enemy ship!\n";
				fire = 2; checkFire = true; 
				board[yF][xF] = "X";								//updates the g_FireAtEnemy[] array for reference by the loop checking that the coordinate has not been previously used and to update the user interface to show the hit
				hitCount++;											//Adds one to the playerHitCount when the player has struck an enemy ship
			}
		}
	}
	void upDateBoard() {
		if (fire == 1) {
			board[yF][xF] = "O";									//updates the g_FireAtEnemy[] array for reference by the loop checking that the coordinate has not been previously used and to update the user interface to show the miss
		}
		if (fire == 2) {
			board[yF][xF] = "X";
		}
	}
	void checkHitCount() {
		if (hitCount == 14) {
			endGame = true;
			std::cout << "Game Over!";
		}
	}
	void fireCoord() {													//Function used for validating that the user input a number between 0 and 9 for the board to fire at 
		do {
			std::cout << "Please enter x coordinate as 0-9" << std::endl;
			getline(std::cin, _fireX);
			xF = atoi(_fireX.c_str());									//Take the user input and converts it to an integer to store in x updating it from its privious value
		} while (0 > xF || xF > 9);
		do {
			std::cout << "Please enter y coordinate as 0-9" << std::endl;
			getline(std::cin, _fireY);
			yF = atoi(_fireY.c_str());									//Take the user input and converts it to an integer to store in x updating it from its privious value
		} while (0 > yF || yF > 9);
	}
};


#endif // !BOARD
