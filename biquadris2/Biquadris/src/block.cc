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

}

void Block::rotateCClockwise(Chunk* chunk)
{

}

bool Block::move(Biquadris::Direction direction, unsigned int shift, Chunk* chunk)
{
	int shiftX = 0, shiftY = 0;

	if (direction == Direction::LEFT)
	{
		shiftX = -(int)shift;
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
				/*if (chunk->getSquares()[(square->position.x + shiftX) + ((square->position.y + shiftY) * GridInfo::GRID_WIDTH)]->status == SquareStatus::ACTIVE)
				{
					contacts = true;
					break;
				}*/
			}
		}
		else
		{
			if (newPosition.x >= GridInfo::GRID_HEIGHT)
			{
				contacts = true;
				break;
			}
			else return true;
		}
	}

	if (contacts && direction == Direction::DOWN)
	{ //The blocks should die
		return false;
	}
	else
	{ //If there is no contact, then move the Block
		for (auto s : this->squares)
		{
			s->position.x += shiftX;
			s->position.y += shiftY;
		}

		if (chunk)
		{
			chunk->deactivateBlock(*this);
			chunk->addBlock(*this);
		}
	}

	return true;
}

const std::vector<Square*>& Block::getSquares() const
{
	return squares;
}
