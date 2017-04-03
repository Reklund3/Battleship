#include "Ship.h"
#include <ctime>
#include <random>
#include <iostream>
#include <algorithm>

uniform_int_distribution<int> o(0, 3), p(0, 9);							//defines the integer variables ranges for random number generation
default_random_engine r(time(0));										//defines the algorithm used to generate random numbers. in this case the computers time clock was used
int xF, yF;

void SHIPS::placeShip(string t) {
	_team = t;
	for (int z = 0; z < 4; z++)
	{
		do {
			checkLoc = true;
			if (_team == "") {
				do {													//Parent loop running until the ship is not overlaping another ship
					do {												//Loop getting users desired ship coordinates. This runs until the ship would be on the board and then exits to the parent loop
						cout << "Please Enter " << shipName[shipSize - 1] << " Desired Direction of Travel as N, E, S, W" << endl;
						getline(cin, direction);
						transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
						if (direction == "n" || direction == "e" || direction == "s" || direction == "w") { break; }
					} while (direction != "n" || direction != "e" || direction != "s" || direction != "w" || direction == ""); //condition to run the loop until the correct input is received
					do {
						cout << "Please enter x coordinate as 0-9" << endl;
						getline(cin, test_X);
						x = atoi(test_X.c_str());											// converts the users input for the variable string X into a integer and stores it in the variable int x
					} while (x < 0 || x > 9);
					do {
						cout << "Please enter y coordinate as 0-9" << endl;
						getline(cin, test_Y);
						y = atoi(test_Y.c_str());											//converts the users input for the variable string Y into a integer and stores it in the variable int y
					} while (y < 0 || y > 9);
					if (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize) {
						cout << "The ships direction and location would place it off the board. Please try again.\n";
					}
				} while (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize);
			}
			if (_team == "e") {
				do {													//This loop runs until the direction, x and y coordinates would not place the ship off the grid.
					_randDirection = o(r);
					x = p(r);
					y = p(r);
					direction = dir[_randDirection];
				} while (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize);
			}
			if (_team == "t") { x = 0; y = 0; }
			for (int i = 0; i <= shipSize; i++) {										//this loop is used to take the users inputs and test make sure that the ship will not overlap another ship.
				if (direction == "n" && board[y + i][x] == "S" ||
					direction == "e" && board[y][x - i] == "S" ||
					direction == "s" && board[y - i][x] == "S" ||
					direction == "w" && board[y][x + i] == "S" ||
					board[y][x] == "S") {
					checkLoc = false;
				}
			}
		} while (checkLoc == false);
		for (int s = 0; s <= shipSize; s++) {
			if (direction == "n") { board[y + s][x] = "S"; }
			if (direction == "e") { board[y][x - s] = "S"; }
			if (direction == "s") { board[y - s][x] = "S"; }
			if (direction == "w") { board[y][x + s] = "S"; }
		} direction = ""; x = -1; y = -1; shipSize++;
	}
}

void SHIPS::fireAtPlayer() {										//The function when called randomly generates coordinates and determines if the coordinates have either been used or are a miss or hit
	do {
		xF = p(r); yF = p(r);
	} while (board[yF][xF] == "X" || board[yF][xF] == "O");
	if (board[yF][xF] == " ") {								//If the coordantes dont hold a ship ("S") than the enemy missed and the condition statment is executed updating the g_PlayerBoard[][] array
		std::cout << "The enemy fired at ( " << xF << " | " << yF << " ) missing your boats!\n" << std::endl;
		board[yF][xF] = "O";
	}
	if (board[yF][xF] == "S") {								//If the coordantes hold a ship ("S") than the enemy hit and the condition statment is executed updating the g_PlayerBoard[][] array
		std::cout << "Crap the enemy fired at ( " << xF << " | " << yF << " ) and hit a ship!\n" << std::endl;
		board[yF][xF] = "X";
		hitCount++;											//Adds one to the hitCountEnemy when the player has struck an enemy ship
	}
}