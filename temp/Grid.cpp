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
			Square square = Square{ Coordinate{ colcount, rowcount }, SquareStatus::DEAD, " " };

			this->squares.at(rowcount).push_back(square);
		}
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

void Grid::UpdateSquare(Coordinate position, Square& square, SquareStatus newSquareStatus)
{
	// y is the row number and x is the col number
	this->squares.at(position.y).at(position.x).squareStatus = newSquareStatus;
	
	if (newSquareStatus == SquareStatus::ACTIVE)
	{
		this->squares.at(position.y).at(position.x).squareSymbol = square.squareSymbol;
	}
	else
	{
		this->squares.at(position.y).at(position.x).squareSymbol = " ";
	}
}

void Grid::ActiveBlockUpdate(SquareStatus squareStatus)
{
	vector<Square*> squares = this->activeBlock->getBlockSquares();

	for (auto square : squares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, *square, squareStatus);
	}
}

void Grid::move(Direction direction)
{
	// todo check if the move will contact anything
	// set the old position on the grid to dead squares
	vector<Square*> oldActiveBlockSquares = this->activeBlock->getBlockSquares();

	for (auto square : oldActiveBlockSquares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, *square, SquareStatus::DEAD);
	}

	// renew the current position
	this->activeBlock->moveBlock(direction);

	vector<Square*> currActiveBlockSquares = this->activeBlock->getBlockSquares();
	for (auto square : currActiveBlockSquares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, *square, SquareStatus::ACTIVE);
	}
}
