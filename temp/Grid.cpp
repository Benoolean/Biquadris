#include <iostream>
#include "Grid.h"
#include "Square.h"
#include "Block.h"

using namespace std;

Grid::Grid()
{
	// delete if there a previous grid members
	delete this->activeBlock;
	this->activeBlock = nullptr;

	// fill the squares in the grid

	int x = 0;
	int y = 0;

	this->squares = vector<vector<Square>>(165);

	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int colcount = 0; colcount < (int) GridInfo::GRID_WIDTH; colcount++)
		{
			Square square = Square{ Coordinate{ x, y }, SquareStatus::DEAD, " " };
			this->squares.at(rowcount).push_back(square);
			x++;
		}
		y++;
	}
}

Grid::~Grid()
{
	delete this->activeBlock;
}

vector<Square>& Grid::getRow(int rowNum)
{
	// where 0 row is row 1
	return this->squares.at(rowNum);
}

void Grid::UpdateSquare(Coordinate position, Square& square)
{
	this->squares.at(position.x).at(position.y).squareStatus = square.squareStatus;
	this->squares.at(position.x).at(position.y).squareSymbol = square.squareSymbol;
}

void Grid::ActiveBlockUpdate()
{
	vector<Square> squares = this->activeBlock->getBlockSquares();

	for (auto square : squares)
	{
		this->UpdateSquare(Coordinate{ square.position.x, square.position.y }, square);
	}
}
