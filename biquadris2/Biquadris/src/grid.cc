#include "../headers/grid.h"
#include "../headers/square.h"
#include "../headers/Chunk.h"

using namespace std;
using namespace Biquadris;

Grid::Grid()
	: chunk(new Chunk()),
	active(nullptr)
{
}

Grid::~Grid()
{
	delete active;
	delete chunk;
}

bool Grid::isActive()
{
	return active;
}

bool Grid::setActive(Block* newActive)
{
	const vector<Square*>& blockSquare = newActive->getSquares();

	for (auto square : blockSquare)
	{
		//Check if the new square contacts any of the existing squares
		SquareStatus squareStatus = square->status;
		
		if (this->chunk->getSquares().at(square->position.y).at(square->position.x)->status == squareStatus)
		{
			this->gridcomplete = true;
			return false;
		}
	}

	active = newActive;
	chunk->addBlock(*active);

	return false;
}

bool Grid::move(Direction direction)
{
	if (active)
	{
		if (!active->move(direction, 1, chunk))
		{ //block made a dying movement
			active = nullptr;
			return false;
		}
	}
	return true;
}

void Grid::checkRowCompleteness()
{

}

vector<vector<Square>> Grid::getPlayerChunk()
{
	vector<vector<Square>> gridcpy = vector<vector<Square>>(Biquadris::GRID_WIDTH * Biquadris::GRID_HEIGHT);


	const vector<vector<Square*>>& chunkSquares = chunk->getSquares();

	for (int rowcount = 0; rowcount < Biquadris::GRID_HEIGHT; rowcount++)
	{
		for (int colcount = 0; colcount < Biquadris::GRID_WIDTH; colcount++)
		{
			Square chunkSquare = *chunkSquares.at(rowcount).at(colcount);
			gridcpy.at(rowcount).push_back(chunkSquare);
		}
	}

	return gridcpy;
}
