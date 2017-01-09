#pragma once
#include "Board.h"
#include <ctime>
#include <random>

using namespace std;

uniform_int_distribution<int> o(0, 3), p(0, 9);							//defines the integer variables ranges for random number generation
default_random_engine r(time(0));										//defines the algorithm used to generate random numbers. in this case the computers time clock was used

class SHIPS : public Board {
protected:
	bool checkLoc;
	const string shipName[4] = { "Cruiser", "Destroyer","Battleship","Carrier" }; //Array used for output statement to user when they are placing their ships on the board in the placeShip member function
	const string dir[4] = { "n", "e", "s", "w" };									//Array used for determining a direction for the heading() member function, it converts the random number to a string output for the conditions within heading()
	int _randDirection;											//declares a member variable used to store the random direction number used to reference a direction in the g_Dir array

public:
	SHIPS(string t) {
		initializeGrid();
		_team = t;
		for (int z = 0; z < 4; z++)
		{
			if (_team == "") {
				do {
					checkLoc = true;										//Sets the g_CheckLoc bool value to true before running the for loop that tests if the ship overlaps another ship. 
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
							if (0 <= x && x <= 9) { break; }									// if this converted value is within the 0 to 9 range the input is valid and the loop is stopped
						} while (true);
						do {
							cout << "Please enter y coordinate as 0-9" << endl;
							getline(cin, test_Y);
							y = atoi(test_Y.c_str());											//converts the users input for the variable string Y into a integer and stores it in the variable int y
							if (0 <= y && y <= 9) { break; }									//if this converted value is within the 0 to 9 range the input is valid and the loop is stopped
						} while (true);
						if (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize) {
							cout << "The ships direction and location would place it off the board. Please try again.\n";
						}
					} while (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize);
					for (int i = 0; i <= shipSize; i++) {										//this loop is used to take the users inputs and test make sure that the ship will not overlap another ship.
						if (board[y][x] == "S") { checkLoc = false; }							//If any of the ships coordinates overlap another ship the g_CheckLoc bool is set to false so that the do while will run again
						if (direction == "n" && board[y + i][x] == "S") { checkLoc = false; }
						if (direction == "e" && board[y][x - i] == "S") { checkLoc = false; }	//in the event that a ship overlaps another already placed ship the m_CheckLoc bool is updated to false causing the main loop to run again
						if (direction == "s" && board[y - i][x] == "S") { checkLoc = false; }
						if (direction == "w" && board[y][x + i] == "S") { checkLoc = false; }
					}
				} while (checkLoc == false);
			}
			if(_team == "e")	{
				do {														//The loop runs until the direction, x and y coordinates would not overlap another ship
					do {													//This loop runs until the direction, x and y coordinates would not place the ship off the grid.
						_randDirection = o(r);
						x = p(r);
						y = p(r);
						direction = dir[_randDirection];
					} while (direction == "n" && y > 9 - shipSize || direction == "e" && x < 0 + shipSize || direction == "s" && y < 0 + shipSize || direction == "w" && x > 9 - shipSize);
					checkLoc = true;											//Sets the g_CheckLoc bool value to true before running the for loop that tests if the ship overlaps another ship. 
					for (int i = 0; i <= shipSize; i++) {						//Loop for checking each cell of the ships position as to make sure the ship does not overlap any already placed ships
						if (board[y][x] == "S") { checkLoc = false; }	//If any of the ships coordinates overlap another ship the g_CheckLoc bool is set to false so that the do while will run again
						if (direction == "n" && board[y + i][x] == "S") { checkLoc = false; }
						if (direction == "e" && board[y][x - i] == "S") { checkLoc = false; }
						if (direction == "s" && board[y - i][x] == "S") { checkLoc = false; }
						if (direction == "w" && board[y][x + i] == "S") { checkLoc = false; }
					}
				} while (checkLoc == false);
			}
			if (direction == "n") {
				for (int s = 0; s <= shipSize; s++) {						//if the direction is north then the following loop is executed a number of time wqual to the size of the ship
					board[y + s][x] = "S";
				}
			}
			if (direction == "e") {
				for (int s = 0; s <= shipSize; s++) {						//if the direction is east then the following loop is executed a number of time wqual to the size of the ship
					board[y][x - s] = "S";
				}
			}
			if (direction == "s") {
				for (int s = 0; s <= shipSize; s++) {						//if the direction is south then the following loop is executed a number of time wqual to the size of the ship
					board[y - s][x] = "S";
				}
			}
			if (direction == "w") {
				for (int s = 0; s <= shipSize; s++) {						//if the direction is west then the following loop is executed a number of time wqual to the size of the ship
					board[y][x + s] = "S";
				}
			} direction = ""; x = -1; y = -1; shipSize++;
		}
	}
	void fireAtPlayer() {										//The function when called randomly generates coordinates and determines if the coordinates have either been used or are a miss or hit
		do {
			xF = p(r); yF = p(r);
		} while (board[yF][xF] == "X" || board[yF][xF] == "O");
		if (board[yF][xF] == " ") {								//If the coordantes dont hold a ship ("S") than the enemy missed and the condition statment is executed updating the g_PlayerBoard[][] array
			std::cout << "The enemy fired at ( " << xF <<  " | " << yF << " ) missing your boats!\n" << std::endl;
			board[yF][xF] = "O";
		}
		if (board[yF][xF] == "S") {								//If the coordantes hold a ship ("S") than the enemy hit and the condition statment is executed updating the g_PlayerBoard[][] array
			std::cout << "Crap the enemy fired at ( " << xF << " | " << yF << " ) and hit a ship!\n" << std::endl;
			board[yF][xF] = "X";
			hitCount++;											//Adds one to the hitCountEnemy when the player has struck an enemy ship
		}
	}
};


