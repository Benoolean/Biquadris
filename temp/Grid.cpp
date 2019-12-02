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

	this->deadBlock = new DeadBlock;
	this->squares = vector<vector<Square*>>(165);

	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int colcount = 0; colcount < (int) GridInfo::GRID_WIDTH; colcount++)
		{
			Square* square = new Square{ Coordinate{ colcount, rowcount }, SquareStatus::INACTIVE, " " };

			this->squares.at(rowcount).push_back(square);
		}
	}
}

Grid::~Grid()
{
	delete this->activeBlock;
}

vector<Square*> Grid::getRow(int rowNum)
{
	// where 0 row is row 1
	return this->squares.at(rowNum);
}

Square* Grid::getNeighbouringSquare(Square* square, Direction direction)
{
	int posx = square->position.x;
	int posy = square->position.y;

	Coordinate neighbouringCoord = Coordinate{ posx, posy }.getNeighbouringCoordinate(direction);

	if (neighbouringCoord.isValidCoord())
	{
		if (direction.getDirection() == DirectionValue::LEFT)
		{
			return this->getRow(square->position.y).at(square->position.x - 1);
		}
		else if (direction.getDirection() == DirectionValue::RIGHT)
		{
			return this->getRow(square->position.y).at(square->position.x + 1);
		}
		else
		{
			return this->getRow(square->position.y + 1).at(square->position.x);
		}
	}

	return new Square{neighbouringCoord, square->squareStatus, square->squareSymbol};
}

void Grid::SpawnNewBlock()
{
	Block* block = new SBlock{};
	this->activeBlock = block;
	this->ActiveBlockUpdate(SquareStatus::ACTIVE);
}

void Grid::UpdateSquare(Coordinate position, Square* square, SquareStatus newSquareStatus)
{
	// y is the row number and x is the col number
	this->squares.at(position.y).at(position.x)->squareStatus = newSquareStatus;
	
	if (newSquareStatus == SquareStatus::ACTIVE)
	{
		this->squares.at(position.y).at(position.x)->squareSymbol = square->squareSymbol;
	}
	else
	{
		this->squares.at(position.y).at(position.x)->squareSymbol = " ";
	}
}

void Grid::ActiveBlockUpdate(SquareStatus squareStatus)
{
	vector<Square*> squares = this->activeBlock->getBlockSquares();

	for (auto square : squares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, square, squareStatus);
	}
}

void Grid::move(Direction direction)
{
	vector<Square*> oldActiveBlockSquares = this->activeBlock->getBlockSquares();

	// check if the move will contact anything
	for (auto square : oldActiveBlockSquares)
	{
		int posx = square->position.x;
		int posy = square->position.y;

		Square* neighbouringSquare = this->getNeighbouringSquare(square, direction);

		// cancel the movement if it will hit a dead square and add to dead block
		if (neighbouringSquare->squareStatus == SquareStatus::DEAD)
		{
			this->AddToDeadBlock();
			return;
		}

		// cancel the movement if the next move will be an invalid square.
		// with the exception that the square is on the bottom. because we need to add it to the
		// deadblocks if the current position is on the bottom and the direction is down 
		if ((!neighbouringSquare->isValidSquare()) && square->position.y < 14)
		{
			return;
		}

		// block has hit the bottom
		if (square->position.y == 14 && direction.getDirection() == DirectionValue::DOWN)
		{
			this->AddToDeadBlock();
			return;
		}
	}

	// set the old position of active on the grid to inactive squares
	for (auto square : oldActiveBlockSquares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, square, SquareStatus::INACTIVE);
	}

	// move the block
	this->activeBlock->moveBlock(direction);

	// renew the grid for the active squares
	vector<Square*> currActiveBlockSquares = this->activeBlock->getBlockSquares();
	for (auto square : currActiveBlockSquares)
	{
		this->UpdateSquare(Coordinate{ square->position.x, square->position.y }, square, SquareStatus::ACTIVE);
	}
}

void Grid::AddToDeadBlock()
{
	this->deadBlock->AddBlockToDeadBlock(this->activeBlock);

	// remove the current active block
	this->activeBlock = nullptr;

	// update the grid
	for (auto square : this->deadBlock->getBlockSquares())
	{
		this->UpdateSquare(square->position, square, SquareStatus::DEAD);
	}

	// spawn new block
	this->SpawnNewBlock();

	// todo: test for any complete rows
}

void Grid::RowCompletenessCheck()
{
	// for each row, we check if the colums are filled
	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		vector<Square*> row = this->getRow(rowcount);

		bool isFilled = true;
		for (auto col : row)
		{
			isFilled = isFilled && (col->squareStatus == SquareStatus::DEAD);
		}

		// remove the row if it is filled
		// and shift everything down (gravity shift)
		if (isFilled)
		{
			DeadBlockGravityShift(rowcount);
		}
	}
}

void Grid::DeadBlockGravityShift(int rowNum)
{
	// get all rows above row n
	for (int rowcount = rowNum; rowcount >= 0; rowcount--)
	{
		// todo get each col (square) and gravity shift it

	}
}
