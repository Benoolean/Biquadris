#pragma once
#include <vector>
#include <string>
#include "Square.h"

enum class BlockType { S, T, I };

// Generic Block:

class Block
{
protected:
	std::string blockSymbol;
	BlockType blockType;
	std::vector<Square> blockSquares;

public:
	// return the symbol that represent the block
	std::string getBlockSymbol()
	{
		return this->blockSymbol;
	}
	 
	// return the squares that make up this block 
	std::vector<Square>& getBlockSquares()
	{
		return this->blockSquares;
	}

	// reposition each square in the block
	void moveBlock(Direction direction)
	{
		bool isValidMove = true;

		for (auto& square : this->blockSquares)
		{
			isValidMove = isValidMove && square.moveSquareAndValidatePosition(direction.getDirection());
		}

		// if the move is invalid, we shift it the opposite direction
		for (auto& square : this->blockSquares)
		{
			isValidMove = isValidMove && square.moveSquareAndValidatePosition(direction.getOppositeDirection());
		}
	}
};

// Decorator Blocks Below:

class SBlock : public Block
{
public:

	// SBlock constructor
	SBlock()
	{
		this->blockSymbol = "S";
		this->blockType = BlockType::S;

		// spawn coords : (4,0) (4,1) (4,2) (5,1)
		Square square = Square{ Coordinate{ 5, 0 }, SquareStatus::ACTIVE, this->blockSymbol };
		this->blockSquares.push_back(square);

		square.position = Coordinate{ 5, 1 };
		this->blockSquares.push_back(square);

		square.position = Coordinate{ 4, 1 };
		this->blockSquares.push_back(square);

		square.position = Coordinate{ 4, 2 };
		this->blockSquares.push_back(square);
	}
};