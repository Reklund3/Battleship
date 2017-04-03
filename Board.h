#ifndef BOARD
#define BOARD

#include <string>

class Board {
protected:	
	std::string board[10][10];
	std::string playerBoard = "";
	std::string _team;
	std::string direction, test_X, test_Y;
	int shipSize = 1, x, y, hitCount = 0;
	std::string _fireX, _fireY;											//defines some local variables to the function that are used to store user inputs to be converted to integers
	

public:
	void initializeGrid();
	
	void createBattleGrid();
	
	void getTarget();

	void upDateBoard();
	
	void checkHitCount();
	
	void fireCoord();
};
#endif // !BOARD