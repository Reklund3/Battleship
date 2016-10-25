#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

string g_PlayerBoard[10][10], g_EnemyBoard[10][10], g_FireAtEnemy[10][10];		//declaring the game board arrays
const string g_ShipName[4] = { "Cruiser", "Destroyer","Battleship","Carrier" }; //Array used for output statement to user when they are placing their ships on the board in the placeShip member function
const string g_Dir[4] = { "n", "e", "s", "w" };									//Array used for determining a direction for the heading() member function, it converts the random number to a string output for the conditions within heading()
string g_Direction;																
string test_X, test_Y;
int x, y, g_ShipSize = 1, g_PlayerHitCount = 0, g_EnemyHitCount = 0;	
bool g_CheckLoc, g_GameOver = false, g_PlayAgain = true;				//declaring the test bools for various check functions.
uniform_int_distribution<int> o(0, 3), p(0, 9);							//defines the integer variables ranges for random number generation
default_random_engine r(time(0));										//defines the algorithm used to generate random numbers. in this case the computers time clock was used

class SHIP {
	int _s, _coordX, _coordY;											//declaration of private class variables used for each objects location
	string _d, _team;

public:
	SHIP(int size, string dir, int x, int y, string t) {				//constructs the SHIP from the user input
		_s = size;														//when constructor is called the following values in the class are set to the values that are passed in from the object creation
		_d = dir;
		_coordX = x;
		_coordY = y;
		_team = t;														//Value is controlled by the object creation
		if (_d == "n") {
			for (int s = 0; s <= g_ShipSize; s++) {						//if the direction is north then the following loop is executed a number of time wqual to the size of the ship
				if (_team == "e") { g_EnemyBoard[y + s][x] = "S"; }
				else { g_PlayerBoard[y + s][x] = "S"; }
			}
		}
		if (_d == "e") {
			for (int s = 0; s <= g_ShipSize; s++) {						//if the direction is east then the following loop is executed a number of time wqual to the size of the ship
				if (_team == "e") { g_EnemyBoard[y][x - s] = "S"; }
				else { g_PlayerBoard[y][x - s] = "S"; }
			}
		}
		if (_d == "s") {
			for (int s = 0; s <= g_ShipSize; s++) {						//if the direction is south then the following loop is executed a number of time wqual to the size of the ship
				if (_team == "e") { g_EnemyBoard[y - s][x] = "S"; }
				else { g_PlayerBoard[y - s][x] = "S"; }
			}
		}
		if (_d == "w") {
			for (int s = 0; s <= g_ShipSize; s++) {						//if the direction is west then the following loop is executed a number of time wqual to the size of the ship
				if (_team == "e") { g_EnemyBoard[y][x + s] = "S"; }
				else { g_PlayerBoard[y][x + s] = "S"; }
			}
		}
		sendShip();
	}
	~SHIP() {}															//class destructor
	string sendShip() {													//getter function that returns the ships position into the player or enemy board
		if (_team == "") {												//this value is passed in from the objects creation and is a fixed value attached to the object (no user input) If it is "" the ship position is returned to the g_PlayerBoard array
			return g_PlayerBoard[y][x];									//returns the constructor functions placement of the ship to the g_PlayerBoard array
		}
		if (_team == "e") {												//this value is passed in from the objects creation and is a fixed value attached to the object (no user input) If it is "e" the ship position is returned to the g_EnemyBoard array
			return g_EnemyBoard[y][x];									//returns the constructor functions placement of the ship to the g_PlayerBoard array
		}
	}
};

void initializeGrid() {												//Function adds a space to each array coordinate to make the board square
	for (int n = 0; n < 10; n++) {
		for (int m = 0; m < 10; m++) {
			g_PlayerBoard[n][m] = " ";
			g_EnemyBoard[n][m] = " ";
			g_FireAtEnemy[n][m] = " ";
		}
	}
}
void createBattleGrid() {											//When called this function will display the players board with a break between each cell of the array
	cout << "Players board\n";										//This is also used for coordinate marks for user reference
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	cout << "   -------------------\n";
	for (int n = 0; n < 10; n++) {
		cout << n << " |";
		for (int m = 0; m < 10; m++) {
			cout << g_PlayerBoard[n][m] << "|";
		}
		cout << endl;
	}
}
void createFiredAtGrid() {											//When called this function will display the enemy board with a break between each cell of the array
	cout << endl << endl << "Enemy Board\n";						//This is also used for coordinate marks for user reference
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	cout << "   -------------------\n";
	for (int n = 0; n < 10; n++) {
		cout << n << " |";
		for (int m = 0; m < 10; m++) {
			cout << g_FireAtEnemy[n][m] << "|";
		}
		cout << endl;
	}
}
void placeShip() {												//Ship member function that requests and validates user inputs for the placement of a ship on the players board
	do {
		g_CheckLoc = true;										//Sets the g_CheckLoc bool value to true before running the for loop that tests if the ship overlaps another ship. 
		do {													//Parent loop running until the ship is not overlaping another ship
			do {												//Loop getting users desired ship coordinates. This runs until the ship would be on the board and then exits to the parent loop
				cout << "Please Enter " << g_ShipName[g_ShipSize - 1] << " Desired Direction of Travel as N, E, S, W" << endl;
				getline(cin, g_Direction);
				transform(g_Direction.begin(), g_Direction.end(), g_Direction.begin(), ::tolower);
				if (g_Direction == "n" || g_Direction == "e" || g_Direction == "s" || g_Direction == "w") { break; }
			} while (g_Direction != "n" || g_Direction != "e" || g_Direction != "s" || g_Direction != "w" || g_Direction == ""); //condition to run the loop until the correct input is received
			do {
				cout << "Please enter x coordinate as 0-9" << endl;
				getline(cin, test_X);
				x = atoi(test_X.c_str());									// converts the users input for the variable string X into a integer and stores it in the variable int x
				if (0 <= x && x <= 9) { break; }							// if this converted value is within the 0 to 9 range the input is valid and the loop is stopped
			} while (true);
			do {
				cout << "Please enter y coordinate as 0-9" << endl;
				getline(cin, test_Y);
				y = atoi(test_Y.c_str());									//converts the users input for the variable string Y into a integer and stores it in the variable int y
				if (0 <= y && y <= 9) { break; }							//if this converted value is within the 0 to 9 range the input is valid and the loop is stopped
			} while (true);
			if (g_Direction == "n" && y > 9 - g_ShipSize || g_Direction == "e" && x < 0 + g_ShipSize || g_Direction == "s" && y < 0 + g_ShipSize || g_Direction == "w" && x > 9 - g_ShipSize) {
				cout << "The ships direction and location would place it off the board. Please try again.\n";
			}
		} while (g_Direction == "n" && y > 9 - g_ShipSize || g_Direction == "e" && x < 0 + g_ShipSize || g_Direction == "s" && y < 0 + g_ShipSize || g_Direction == "w" && x > 9 - g_ShipSize);
		for (int i = 0; i <= g_ShipSize; i++) {						//this loop is used to take the users inputs and test make sure that the ship will not overlap another ship.
			if (g_PlayerBoard[y][x] == "S") { g_CheckLoc = false; } //If any of the ships coordinates overlap another ship the g_CheckLoc bool is set to false so that the do while will run again
			if (g_Direction == "n" && g_PlayerBoard[y + i][x] == "S") { g_CheckLoc = false; }
			if (g_Direction == "e" && g_PlayerBoard[y][x - i] == "S") { g_CheckLoc = false; } //in the event that a ship overlaps another already placed ship the m_CheckLoc bool is updated to false causing the main loop to run again
			if (g_Direction == "s" && g_PlayerBoard[y - i][x] == "S") { g_CheckLoc = false; }
			if (g_Direction == "w" && g_PlayerBoard[y][x + i] == "S") { g_CheckLoc = false; }
		}
	} while (g_CheckLoc == false);
}
void randNum() {												//randNum() member function generates the random inputs for placing enemy ships
	int _randDirection;											//declares a member variable used to store the random direction number used to reference a direction in the g_Dir array
	do {														//The loop runs until the direction, x and y coordinates would not overlap another ship
		do {													//This loop runs until the direction, x and y coordinates would not place the ship off the grid.
			_randDirection = o(r);
			x = p(r);
			y = p(r);
			g_Direction = g_Dir[_randDirection];
		} while (g_Direction == "n" && y > 9 - g_ShipSize || g_Direction == "e" && x < 0 + g_ShipSize || g_Direction == "s" && y < 0 + g_ShipSize || g_Direction == "w" && x > 9 - g_ShipSize);
		g_CheckLoc = true;											//Sets the g_CheckLoc bool value to true before running the for loop that tests if the ship overlaps another ship. 
		for (int i = 0; i <= g_ShipSize; i++) {						//Loop for checking each cell of the ships position as to make sure the ship does not overlap any already placed ships
			if (g_EnemyBoard[y][x] == "S") { g_CheckLoc = false; }	//If any of the ships coordinates overlap another ship the g_CheckLoc bool is set to false so that the do while will run again
			if (g_Direction == "n" && g_EnemyBoard[y + i][x] == "S") { g_CheckLoc = false; }
			if (g_Direction == "e" && g_EnemyBoard[y][x - i] == "S") { g_CheckLoc = false; }
			if (g_Direction == "s" && g_EnemyBoard[y - i][x] == "S") { g_CheckLoc = false; }
			if (g_Direction == "w" && g_EnemyBoard[y][x + i] == "S") { g_CheckLoc = false; }
		}
	} while (g_CheckLoc == false);
}
void fireCoord() {													//Function used for validating that the user input a number between 0 and 9 for the board to fire at 
	string _fireX, _fireY;											//defines some local variables to the function that are used to store user inputs to be converted to integers
	do {
		cout << "Please enter x coordinate as 0-9" << endl;
		getline(cin, _fireX);
		x = atoi(_fireX.c_str());									//Take the user input and converts it to an integer to store in x updating it from its privious value
		if (0 <= x && x <= 9) { break; }							//If the value stored in x was greater of equal to zero and less than or equal to 9 then the loop requesting user to input the x coordinate breaks
	} while (true);
	do {
		cout << "Please enter y coordinate as 0-9" << endl;
		getline(cin, _fireY);
		y = atoi(_fireY.c_str());									//Take the user input and converts it to an integer to store in x updating it from its privious value
		if (0 <= y && y <= 9) { break; }							//If the value stored in x was greater of equal to zero and less than or equal to 9 then the loop requesting user to input the x coordinate breaks
	} while (true);
}
void playerFireAtEnemy() {									//Function used for taking users desired firing solution and checking if the user has fired at that location and checks if the target was a hit or miss.
	cout << endl << "Get Ready to fire at the Enemy!\n";
	fireCoord();
	while (g_FireAtEnemy[y][x] == "X" || g_FireAtEnemy[y][x] == "O") {//Loop for testing if the user has entered new coordinates that have not been previously used
		if (g_FireAtEnemy[y][x] == "X") {
			while (g_FireAtEnemy[y][x] == "X") {
				cout << "You have already fired and hit a target at this location. Please enter a new firing solution" << endl << endl;
				fireCoord();
			}
		}
		if (g_FireAtEnemy[y][x] == "O") {
			while (g_FireAtEnemy[y][x] == "O") {
				cout << "You have already fired and missed your target at this location. Please enter a new firing solution" << endl << endl;
				fireCoord();
			}
		}
	}
	if (g_EnemyBoard[y][x] == " ") {								//If the array does not hold a ship ("S") than the following condition statement is run prompting the user and updating the boards
		cout << "You have missed the target, better luck next time" << endl;
		g_FireAtEnemy[y][x] = "O";									//updates the g_FireAtEnemy[] array for reference by the loop checking that the coordinate has not been previously used and to update the user interface to show the miss
	}
	if (g_EnemyBoard[y][x] == "S") {								//If the array does hold a ship ("S") than the following condition statement is run prompting the user and updating the boards and adding to the players hitcount
		cout << "Congratulations, you have hit an enemy ship!" << endl;
		g_FireAtEnemy[y][x] = "X";									//updates the g_FireAtEnemy[] array for reference by the loop checking that the coordinate has not been previously used and to update the user interface to show the hit
		g_PlayerHitCount++;											//Adds one to the playerHitCount when the player has struck an enemy ship
	}
}
void fireAtPlayer() {										//The function when called randomly generates coordinates and determines if the coordinates have either been used or are a miss or hit
	do {
		x = p(r), y = p(r);
	} while (g_PlayerBoard[y][x] == "X" || g_PlayerBoard[y][x] == "O");
	if (g_PlayerBoard[y][x] == " ") {								//If the coordantes dont hold a ship ("S") than the enemy missed and the condition statment is executed updating the g_PlayerBoard[][] array
		cout << "The enemy has missed your boats! whew" << endl;
		g_PlayerBoard[y][x] = "O";
	}
	if (g_PlayerBoard[y][x] == "S") {								//If the coordantes hold a ship ("S") than the enemy hit and the condition statment is executed updating the g_PlayerBoard[][] array
		cout << "Crap the enemy has hit your ship!" << endl;
		g_PlayerBoard[y][x] = "X";
		g_EnemyHitCount++;											//Adds one to the hitCountEnemy when the player has struck an enemy ship
	}
}
void endGame() {													//Function to prompt the user to see if they would like to play again 
	int gameState = 0;
	string again;
	do {
		cout << "Would you like to play again? \nTo continue please enter Yes(y) or No(n) to stop playing.\n";
		getline(cin, again);
		transform(again.begin(), again.end(), again.begin(), ::tolower);
		if (again == "y" || again == "yes") {
			g_GameOver = false;										//if this condition is met then the gameOver bool value is updated from true to false
			g_EnemyHitCount = 0;									//resets the player and enemey hit counts to 0 for the start of a new game
			g_PlayerHitCount = 0;
			g_ShipSize = 1;											//resets the g_ShipSize variable to the default value of 1
			cout << "Get ready for another round\n";
			gameState = 1;
		}
		else if (again == "n" || again == "no") {
			g_PlayAgain = false;									//if the condition is met than the playAgain bool value is updated from true to false
			cout << "Thank you for Playing\n";
			gameState = 1;
		}
		else { cout << "incorrect entry please try again\n"; }		//if neither of the above conditions are med than the loop is repeated to get the users input
	} while (gameState != 1);
}
void buildGame() {															//Function requests the user to place their ships on the board and then generates the enemy board.
	placeShip();															//Function requesing and validating the user to enter the Cruisers direction and location, At this point g_ShipSize is defaulted to one
	SHIP Cruiser(g_ShipSize, g_Direction, x, y, "");						//Creates the Cruiser object of ship and passes the user input into the class constructor which intializes the Cruiser class object
	system("CLS");

	createBattleGrid();
	g_ShipSize = 2;															//Sets g_ShipSize to 2 from 1 for the Destroyer ship objects size on the board
	placeShip();															//Function requesing and validating the user to enter the Destroyers direction and location, At this point g_ShipSize is defaulted to one
	SHIP Destroyer(g_ShipSize, g_Direction, x, y, "");						//Creates the Destroyer object of ship and passes the user input into the class constructor which intializes the Destroyer class object
	system("CLS");

	createBattleGrid();
	g_ShipSize = 3;															//Sets g_ShipSize to 3 from 2 for the Battleship ship objects size on the board
	placeShip();															//Function requesing and validating the user to enter the Battleship direction and location, At this point g_ShipSize is defaulted to one
	SHIP Battleship(g_ShipSize, g_Direction, x, y, "");						//Creates the Battleship object of ship and passes the user input into the class constructor which intializes the Destroyer class object
	system("CLS");

	createBattleGrid();
	g_ShipSize = 4;															//Sets g_ShipSize to 4 from 3 for the Carrier ship objects size on the board
	placeShip();															//Function requesing and validating the user to enter the Carriers direction and location, At this point g_ShipSize is defaulted to one
	SHIP Carrier(g_ShipSize, g_Direction, x, y, "");						//Creates the Carrier object of ship and passes the user input into the class constructor which intializes the Destroyer class object

	g_ShipSize = 1;															//Sets g_ShipSize to 1 from 4 for the enemy Cruiser ship objects size on the board
	randNum();																//Function call generating and updating the direction, x, and y variables for placing of enemy ship
	SHIP EnemyCruiser(g_ShipSize, g_Direction, x, y, "e");					//Creates the enemy Cruiser object of ship and passes the user input into the class constructor which intializes the enemy cruiser class object

	g_ShipSize = 2;															//Sets g_ShipSize to 2 from 1 for the enemy Destroyer ship objects size on the board
	randNum();																//Function call generating and updating the direction, x, and y variables for placing of enemy ship
	SHIP EnemyDestroyer(g_ShipSize, g_Direction, x, y, "e");				//Creates the enemy destroyer object of ship and passes the user input into the class constructor which intializes the enemy Destroyer class object

	g_ShipSize = 3;															//Sets g_ShipSize to 3 from 2 for the enemy Battleship ship objects size on the board
	randNum();																//Function call generating and updating the direction, x, and y variables for placing of enemy ship
	SHIP EnemyBattleship(g_ShipSize, g_Direction, x, y, "e");				//Creates the enemy battleship object of ship and passes the user input into the class constructor which intializes the enemy battlship class object

	g_ShipSize = 4;															//Sets g_ShipSize to 4 from 3 for the enemy Carrier ship objects size on the board
	randNum();																//Function call generating and updating the direction, x, and y variables for placing of enemy ship
	SHIP EnemyCarrier(g_ShipSize, g_Direction, x, y, "e");					//Creates the enemy Carrier object of ship and passes the user input into the class constructor which intializes the enemy carrier class object
	system("CLS");
}