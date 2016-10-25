// Below are the applicable versions 
/* Microsoft Visual Studio Community 2015
Version 14.0.25425.01 Update 3
Microsoft.NET Framework
Version 4.6.01055

Installed Version : Community

Visual Basic 2015   00322 - 20000 - 00000 - AA381
Microsoft Visual Basic 2015

Visual C++ 2015   00322 - 20000 - 00000 - AA381
Microsoft Visual C++ 2015

Application Insights Tools for Visual Studio Package   7.7.10922.3
Application Insights Tools for Visual Studio

ASP.NET and Web Tools 2015.1   14.1.20810.0
ASP.NET and Web Tools 2015.1

ASP.NET Web Frameworks and Tools 2012.2   4.1.41102.0
For additional information, visit http ://go.microsoft.com/fwlink/?LinkID=309563

ASP.NET Web Frameworks and Tools 2013   5.2.40314.0
For additional information, visit http ://www.asp.net/

GitHub.VisualStudio   1.0
A Visual Studio Extension that brings the GitHub Flow into Visual Studio.

JavaScript Language Service   2.0
JavaScript Language Service

JavaScript Project System   2.0
JavaScript Project System

Microsoft.NET Core Tools(Preview 2)   14.1.20810.0
Microsoft.NET Core Tools(Preview 2)

PreEmptive Analytics Visualizer   1.2
Microsoft Visual Studio extension to visualize aggregated summaries from the PreEmptive Analytics product.

TypeScript   1.8.36.0
TypeScript tools for Visual Studio

Visual Studio Tools for Unity   2.3.0.0
Visual Studio Tools for Unity

Visual Studio Tools for Universal Windows Apps   14.0.25527.01
The Visual Studio Tools for Universal Windows apps allow you to build a single universal app experience that can reach every device running Windows 10: phone, tablet, PC, and more.It includes the Microsoft Windows 10 Software Development Kit.

This was developed and compiled on a Windows 7 Service Pack 1
*/

#include "battleShip.h"

int main()
{
	while (g_PlayAgain == true) {						//Starts the main game loop. playAgain 
		initializeGrid();
		createBattleGrid();								//displays the players board, the function is located in the battlShip.h file
		buildGame();									//Requests the user to place ships and generates enemy board when called
		
		while (g_GameOver == false) {					//once the game state has been established and all boats are placed correctly the games primary firing loop starts
			createBattleGrid();							//displays the players board, the function is located in the battlShip.h file
			createFiredAtGrid();						//displays the enemys board as blank as the user does not know the enemay ships placement, the function is located in the battlShip.h file
			playerFireAtEnemy();						//calls for the user to enter firing coordinates
			system("CLS");
			if (g_PlayerHitCount == 14) {				//condition statement checking to determine if the player has sunk all of the enemys ships
				cout << "You Win" << endl;
				g_GameOver = true;						//updates the gameOver bool value from false to true to break the primary firing loop
			}
			if (g_EnemyHitCount == 14) {				//condition statement checking to determine if the enemy has sunk all of the players ships
				cout << "You Lose" << endl;
				g_GameOver = true;						//updates the gameOver bool value from false to true to break the primary firing loop
			}
			fireAtPlayer();								//calls the function to generate a coordinates to fire at the player
		}
		endGame();										//Function to determine if the user would like to play again
	}
	return 0;
}