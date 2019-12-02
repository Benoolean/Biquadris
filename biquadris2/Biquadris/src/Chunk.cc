#include "../headers/Chunk.h"
#include "../headers/square.h"

#include "../headers/biquadris.h"

#include <iostream>

using namespace std;
using namespace Biquadris;

Chunk::Chunk()
	: squares{vector<vector<Square*>>((int) GridInfo::GRID_HEIGHT * (int)GridInfo::GRID_WIDTH)}
{
	for (int rowcount = 0; rowcount < (int)GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int colcount = 0; colcount < (int)GridInfo::GRID_WIDTH; colcount++)
		{
			Square* square = new Square{ colcount, rowcount, " ", 0, SquareStatus::INACTIVE };

			this->squares.at(rowcount).push_back(square);
		}
	}
}

Chunk::~Chunk()
{
	for (auto row : squares)
	{
		for (auto col : row)
		{
			delete col;
		}
	}
}

void Chunk::addBlock(const Block& block)
{
	const vector<Square*>& blockSquares = block.getSquares();
	for (auto square : blockSquares)
	{
		this->squares.at(square->position.y).at(square->position.x)->mimic(*square);
	}
}

void Chunk::deactivateBlock(const Block& b)
{
	const vector<Square*>& blockSquares = b.getSquares();
	for (auto square : blockSquares)
	{
		this->squares.at(square->position.y).at(square->position.x)->deactivate();
	}
}

void Chunk::addSquare(const Square& square)
{
	this->squares.at(square.position.y).at(square.position.x)->mimic(square);
}

void Chunk::deactivateSquare(const Square& square)
{
	this->squares.at(square.position.y).at(square.position.x)->deactivate();
}

const vector<vector<Square*>>& Chunk::getSquares() const
{
	return squares;
}
