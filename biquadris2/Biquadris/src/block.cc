#include "../headers/coordinate.h"
#include "../headers/block.h"
#include "../headers/square.h"
#include "../headers/Chunk.h"
using namespace std;
using namespace Biquadris;

Block::Block() {}

Block::Block(std::vector<Square*>&& squares)
{
	this->squares.swap(squares);
}

Block::Block(const Block& other)
{
	const vector<Square*>& otherSquares = other.getSquares();
	for (int i = 0; i < otherSquares.size(); i++)
	{
		this->squares.push_back(new Square(*otherSquares[i]));
	}
}

Block::~Block()
{
	for (auto square : squares)
	{
		delete square;
	}
}

void Block::rotateClockwise(Chunk* chunk)
{
	this->rotateCClockwise();
	this->rotateCClockwise();
	this->rotateCClockwise();
}

void Block::rotateCClockwise(Chunk* chunk)
{
	vector<Square*> squares = this->getSquares();

	// algorithm
	// multiply by matrix[ (0 -1) (1 0)] and offset it with pivital

	vector<Coordinate> squareCoordinates;
	for (auto square : squares)
	{
		squareCoordinates.push_back(Coordinate{ square->position.x, square->position.y });
	}

	vector<Coordinate> squareCoordinatesAfterOriginRotation;
	for (auto square : squares)
	{
		Coordinate rotationFromOrigin = getCounterClockWiseRotationCoord(square);
		squareCoordinatesAfterOriginRotation.push_back(rotationFromOrigin);
	}

	// get pivitol coords for both before and after transformation
	Coordinate squarePivitol = getPivitolCoordinate(squareCoordinates);
	Coordinate squarePivitolAfterOriginRotation = getPivitolCoordinate(squareCoordinatesAfterOriginRotation);

	// find the shift value
	int shiftx = squarePivitolAfterOriginRotation.x - squarePivitol.x;
	int shifty = squarePivitolAfterOriginRotation.y - squarePivitol.y;

	// for each coord in the transformed coords, apply shift
	for (auto & coord : squareCoordinatesAfterOriginRotation)
	{
		coord.x = coord.x - shiftx;
		coord.y = coord.y - shifty;

		//coord = Coordinate{ coord.x , coord.y };
	}

	// check if the rotation is valid -> hence all squares at chunk with squareCoordinatesAfterOriginRotation
	// must be inactive and valid
	for (auto coord : squareCoordinatesAfterOriginRotation)
	{
		if (!coord.isValidCoord())
		{
			return;
		}
	}

	// deactive the current active block
	for (auto coord : squareCoordinates)
	{
		chunk->deactivateCoordinate(coord);
	}
	
	// for the current active block, update the square coordinates
	// and the chunk squares
	for (int squarecount = 0; squarecount < squares.size(); squarecount++)
	{
		Coordinate newCoord = squareCoordinatesAfterOriginRotation.at(squarecount);
		squares.at(squarecount)->position.x = newCoord.x;
		squares.at(squarecount)->position.y = newCoord.y;

		chunk->addSquare(*squares.at(squarecount));
	}
}

bool Block::move(Biquadris::Direction direction, int shift, Chunk* chunk)
{
	int shiftX = 0, shiftY = 0;

	if (direction == Direction::LEFT)
	{
		shiftX = -shift;
	}
	else if (direction == Direction::RIGHT)
	{
		shiftX = shift;
	}
	else if (direction == Direction::DOWN)
	{
		shiftY = shift;
	}

	bool contacts = false;

	for (auto square : this->squares)
	{
		Coordinate newPosition{ square->position.x + shiftX, square->position.y + shiftY };
		if (newPosition.isValidCoord())
		{
			if (chunk)
			{
				int posx = square->position.x + shiftX;
				int posy = square->position.y + shiftY;

				if (chunk->getSquares().at(posy).at(posx)->status == SquareStatus::DEAD)
				{
					contacts = true;
					break;
				}
			}
		}
		else
		{
			if (newPosition.y >= GridInfo::GRID_HEIGHT)
			{
				contacts = true;
				break;
			}
			else return true;
		}
	}

	if (contacts && direction == Direction::DOWN)
	{ //The blocks should die
		chunk->killBlock(*this);
		return false;
	}
	else
	{ 
		//If there is no contact, then move the Block
		if(chunk) {
			chunk->deactivateBlock(*this);
		}

		for (auto s : this->squares)
		{
			s->position.x += shiftX;
			s->position.y += shiftY;
		}

		if (chunk)
		{
			chunk->addBlock(*this);
		}
	}

	return true;
}

const std::vector<Square*>& Block::getSquares() const
{
	return squares;
}
