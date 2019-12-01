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
			vector<Square> row = (playerNum == 1) ? this->playerOneGrid->getRow(rowcount) : this->playerTwoGrid->getRow(rowcount);

			for (auto col : row)
			{
				if (col.squareStatus == SquareStatus::INACTIVE)
				{
					cout << " ";
				}
				else if (col.squareStatus == SquareStatus::ACTIVE)
				{
					char c = (int) LevelBlockSymbol::ACTIVE_BLOCK_SYMBOL;
					cout << c;
				}
				else if (col.squareStatus == SquareStatus::DEAD)
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
}

void Level::SpawnBlock(Grid* playerGrid)
{
	
	// hardcoded for now
	Block * block = new SBlock{};
	playerGrid->activeBlock = block;

	playerGrid->ActiveBlockUpdate(SquareStatus::ACTIVE);

	this->printGrid();
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

	this->printGrid();
}
