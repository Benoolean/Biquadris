#include "../headers/grid.h"
#include "../headers/square.h"
#include "../headers/Chunk.h"

using namespace std;
using namespace Biquadris;

Grid::Grid()
	: chunk{ new Chunk() }, active{ nullptr }, gridcomplete{ false }
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
		if (this->chunk->getSquares().at(square->position.y).at(square->position.x)->status == SquareStatus::DEAD)
		{
			this->gridcomplete = true;

			delete this->active;
			return false;
		}
	}

	if(this->active) {
		this->chunk->deactivateLiveBlock(*this->active);
		delete this->active;
	}

	this->active = newActive;
	this->chunk->addBlock(*this->active);

	return true;
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

int Grid::checkRowCompleteness()
{
	return chunk->clearFullRows();
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
