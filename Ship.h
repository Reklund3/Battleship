#ifndef SHIPS_H
#define SHIPS_H

#include "Board.h"

using namespace std;

class SHIPS : public Board {
protected:
	bool checkLoc;
	const string shipName[4] = { "Cruiser", "Destroyer","Battleship","Carrier" }; //Array used for output statement to user when they are placing their ships on the board in the placeShip member function
	const string dir[4] = { "n", "e", "s", "w" };									//Array used for determining a direction for the heading() member function, it converts the random number to a string output for the conditions within heading()
	int _randDirection;											//declares a member variable used to store the random direction number used to reference a direction in the g_Dir array

public:
	SHIPS(string t) {
		initializeGrid();
		placeShip(t);
	}
	void fireAtPlayer();
	void placeShip(string t);
};

#endif