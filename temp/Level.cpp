#include <iostream>
#include "Level.h"
#include "Block.h"
#include "Square.h"
#include "Grid.h"

using namespace std;

// constants
string GRID_SEPERATION_SPACE = "    ";
string GRID_BAR_SEPERATOR = "-----------" + GRID_SEPERATION_SPACE + "-----------";

void Level::StartGame()
{
	this->playerOneGrid = new Grid();
	this->playerTwoGrid = new Grid();

	this->playerOneGrid->SpawnNewBlock();
	this->playerTwoGrid->SpawnNewBlock();

	this->printGrid();

	// read in the command inputs
	string cmd = "";

	while (cin >> cmd)
	{
		if (cmd == "left")
		{
			this->move(Direction{ DirectionValue::LEFT });
		}
		else if (cmd == "right")
		{
			this->move(Direction{ DirectionValue::RIGHT });
		}
		else if (cmd == "down")
		{
			this->move(Direction{ DirectionValue::DOWN });
		}
	}
}

void Level::printGrid()
{ 
	/*========= print level and score =========*/

	// todo dynanmic spacing based on score

	cout << "Level:" << "    " << "1" << GRID_SEPERATION_SPACE <<"Level:" << "    " << "1" << endl;
	cout << "Score:" << "    " << "1" << GRID_SEPERATION_SPACE << "Score:" << "    " << "1" << endl;

	/*========= print grid =========*/

	cout << GRID_BAR_SEPERATOR << endl;

	// print each row by player count
	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int playerNum = 1; playerNum <= (int)LevelInfo::MAX_PLAYERS; playerNum++)
		{
			vector<Square*> row = (playerNum == 1) ? this->playerOneGrid->getRow(rowcount) : this->playerTwoGrid->getRow(rowcount);

			for (auto col : row)
			{
				if (col->squareStatus == SquareStatus::INACTIVE)
				{
					cout << " ";
				}
				else if (col->squareStatus == SquareStatus::ACTIVE)
				{
					char c = (int) LevelBlockSymbol::ACTIVE_BLOCK_SYMBOL;
					cout << c;
				}
				else if (col->squareStatus == SquareStatus::DEAD)
				{
					char c = (int)LevelBlockSymbol::DEAD_BLOCK_SYMBOL;;
					cout << c;
				}
			}
			cout << GRID_SEPERATION_SPACE;
		}

		cout << endl;
	}

	cout << GRID_BAR_SEPERATOR << endl;

	/*========= print next=========*/
	
	cout << "Next:" << endl;
}

void Level::move(Direction direction)
{
	if (this->isPlayerOneTurn)
	{
		this->playerOneGrid->move(direction);
	}
	else
	{
		this->playerTwoGrid->move(direction);
	}

	this->isPlayerOneTurn = !this->isPlayerOneTurn;

	this->printGrid();
}
