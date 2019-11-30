#pragma once
#include <string>
#include <iostream>

enum class SquareStatus { ACTIVE, DEAD };
enum class DirectionValue { LEFT, RIGHT, DOWN };

class Direction
{
	DirectionValue direction;
public:
	Direction(DirectionValue direction) : direction{ direction } {};

	// return direction value
	DirectionValue getDirection()
	{
		return this->direction;
	}

	// returns the opposite horizontal direction
	DirectionValue getOppositeDirection()
	{
		return (this->direction == DirectionValue::LEFT) ? DirectionValue::RIGHT : DirectionValue::LEFT;
	}
};

// (0,0) is the top right of the grid
struct Coordinate
{
	int x;
	int y;

	bool isValidCoord()
	{
		return (x >= 0 && x <= 10 && y >= 0 && y <= 14);
	}
};

struct Square
{
	Coordinate position;
	
	SquareStatus squareStatus;

	std::string squareSymbol;

	bool moveSquareAndValidatePosition(DirectionValue direction)
	{
		// shift the coords of the square
		if (direction == DirectionValue::LEFT)
		{
			this->position.x--;
		}
		else if (direction == DirectionValue::RIGHT)
		{
			this->position.x++;
		}

		// return false if the move is invalid
		return this->position.isValidCoord();
	}
};

