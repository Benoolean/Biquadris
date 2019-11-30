#include <iostream>
#include "Level.h"
#include "Block.h"
#include "Grid.h"

using namespace std;

// constants
string GRID_SEPERATION_SPACE = "    ";
string GRID_BAR_SEPERATOR = "-----------" + GRID_SEPERATION_SPACE + "-----------";

void Level::StartGame()
{
	this->playerOneGrid = new Grid();
	this->playerTwoGrid = new Grid();

	this->printGrid();
}

void Level::printGrid()
{
	cout << GRID_BAR_SEPERATOR << endl;

	// print each row by player count
	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int playerNum = 1; playerNum <= (int)LevelInfo::MAX_PLAYERS; playerNum++)
		{
			vector<Square> row = this->playerOneGrid->getRow(rowcount);

			for (auto col : row)
			{
				if (col.squareStatus == SquareStatus::DEAD)
				{
					cout << " ";
				}
				else if (col.squareStatus == SquareStatus::ACTIVE)
				{
					cout << col.squareSymbol;
				}
			}
			cout << GRID_SEPERATION_SPACE;
		}

		cout << endl;
	}

	cout << GRID_BAR_SEPERATOR << endl;
}

void Level::SpawnBlock()
{
	// hardcoded for now
	Block * block = new SBlock{};
	this->playerOneGrid->activeBlock = block;

	this->playerOneGrid->ActiveBlockUpdate();

	this->printGrid();
}
