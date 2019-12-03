#include "../headers/Chunk.h"
#include "../headers/square.h"

#include "../headers/biquadris.h"

#include <iostream>

using namespace std;
using namespace Biquadris;

Chunk::Chunk()
	: squares{ vector<vector<Square*>>((int)GridInfo::GRID_HEIGHT) }
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

void Chunk::deactivateLiveBlock(const Block& b)
{
	const vector<Square*>& blockSquares = b.getSquares();
	for (auto square : blockSquares)
	{
		Square* s = this->squares.at(square->position.y).at(square->position.x);
		if (s->status == SquareStatus::ACTIVE) s->deactivate();
	}
}

void Chunk::killBlock(const Block& b)
{
	const vector<Square*>& blockSquares = b.getSquares();
	for (auto square : blockSquares)
	{
		this->squares.at(square->position.y).at(square->position.x)->kill();
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

void Chunk::deactivateCoordinate(Coordinate coord)
{
	this->squares.at(coord.y).at(coord.x)->deactivate();
}

int Chunk::clearFullRows()
{
	int rowsCleared = 0;

	int rowIndex = 0;
	for (auto row : this->squares)
	{
		bool fullRow = (squares.size() > 0);
		for (auto square : row)
		{
			if (square->status != SquareStatus::DEAD)
			{
				fullRow = false;
				break;
			}
		}

		if (fullRow)
		{
			++rowsCleared;
			vector<Square> lastRow;
			for (int i = 0; i <= rowIndex; i++)
			{
				vector<Square> tempRow;
				for (auto square : squares[i])
				{
					tempRow.push_back(*square);
					square->deactivate();
				}

				if (i)
				{ //If not the first row
					for (int j = 0; j < (int)squares[i].size(); j++)
					{
						squares[i][j]->mimic(lastRow[j]);
					}
				}

				//Swap the data, to avoid unneccessary copying
				lastRow.swap(tempRow);
			}
		}

		++rowIndex;
	}

	return rowsCleared;
}

const vector<vector<Square*>>& Chunk::getSquares() const
{
	return squares;
}
