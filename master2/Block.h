#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include <iostream>
#include "Square.h"

enum class BlockType { S, T, I };
const int BLOCK_SQUARE_COUNT = 4;

// Generic Block:

class Block
{
protected:
	std::string blockSymbol;
	BlockType blockType;
	std::vector<Square *> blockSquares;

public:
	// return the symbol that represent the block
	std::string getBlockSymbol()
	{
		return this->blockSymbol;
	}
	 
	// return the squares that make up this block 
	std::vector<Square*> getBlockSquares()
	{
		return this->blockSquares;
	}

	// reposition each square in the block
	void moveBlock(Direction direction)
	{
		for (auto square : this->getBlockSquares())
		{
			square->moveSquareAndValidatePosition(direction.getDirection());
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
		Square * square1 = new Square{ Coordinate{ 0, 4 }, SquareStatus::ACTIVE, this->blockSymbol };
		this->blockSquares.push_back(square1);

		Square* square2 = new Square{ Coordinate{ 1, 4 }, SquareStatus::ACTIVE, this->blockSymbol };
		this->blockSquares.push_back(square2);

		Square* square3 = new Square{ Coordinate{ 1, 3 }, SquareStatus::ACTIVE, this->blockSymbol };
		this->blockSquares.push_back(square3);

		Square* square4 = new Square{ Coordinate{ 2, 3 }, SquareStatus::ACTIVE, this->blockSymbol };
		this->blockSquares.push_back(square4);
	}
};

// dead block

class DeadBlock
{
	std::vector<Square*> deadSquares;

public:
	//DeadBlock() {};

	// add squares to the deadblock
	void AddBlockToDeadBlock(Block* block)
	{
		for (auto& square : block->getBlockSquares())
		{
			square->squareStatus = SquareStatus::DEAD;
			this->deadSquares.push_back(square);
		}
	}

	std::vector<Square*> getBlockSquares()
	{
		return this->deadSquares;
	}
};

#endif // !BLOCK_H
