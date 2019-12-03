#include <iostream>

#include "../headers/square.h"
using namespace Biquadris;
using namespace std;

const string Square::emptySymbol = " ";

Square::Square(int x, int y, string symbol, int colour, SquareStatus status)
	: position({ x, y }), symbol(symbol), colour(colour), status(status), uid(-1)
{
}

bool Square::validPosition()
{
	return position.isValidCoord();
}

bool Square::move(Direction direction, unsigned int shift)
{
	// shift the coords of the square
	if (direction == Direction::LEFT)
	{
		this->position.x -= shift;
	}
	else if (direction == Direction::RIGHT)
	{
		this->position.x += shift;
	}
	else if (direction == Direction::DOWN)
	{
		this->position.y += shift;
	}

	return validPosition();
}

void Square::kill()
{
	this->status = SquareStatus::DEAD;
}

void Square::deactivate()
{
	symbol = emptySymbol;
	this->status = SquareStatus::INACTIVE;
	this->uid = -1;
}

void Square::mimic(const Square& s)
{
	this->symbol = s.symbol;
	this->colour = s.colour;
	this->status = s.status;
	this->uid = s.uid;
}

Coordinate getCounterClockWiseRotationCoord(Square* square)
{
	int newx = square->position.y;
	int newy = -1 * square->position.x;
	Coordinate rotationFromOrigin = Coordinate{ newx, newy };

	return rotationFromOrigin;
}

Coordinate getPivitolCoordinate(vector<Coordinate> coords)
{
	// the pivitol coord is the bottom left coord. hence we want the
	// smallest x and largest y
	try
	{
		int minx = coords.at(0).x;
		int maxy = coords.at(0).y;

		for (auto coord : coords)
		{
			minx = (coord.x <= minx) ? coord.x : minx;
			maxy = (coord.y >= maxy) ? coord.y : maxy;
		}

		return Coordinate{ minx, maxy };
	}
	catch (exception const& expect)
	{
		// throw error
		cout << "Unable to return minimal x value in coordinate.cc!" << endl;
		cout << "Exception caused by: " << expect.what() << endl;
	}
}
