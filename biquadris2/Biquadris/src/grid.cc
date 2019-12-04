#include "../headers/grid.h"
#include "../headers/square.h"
#include "../headers/Chunk.h"

#include <cmath>

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

	for(auto block : deadBlocks) {
		delete block;
	}
}

Chunk* Grid::getChunk() {
	return this->chunk;
}

bool Grid::isActive()
{
	return active != nullptr;
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
		this->chunk->deactivateBlock(*this->active);
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
			deadBlocks.push_back(active);
			active = nullptr;
			return false;
		}
	}
	return true;
}

void Grid::rotateCClockwise()
{
	if (this->active)
	{
		this->active->rotateCClockwise(this->chunk);
	}
}

int Grid::checkRowCompleteness()
{
	return chunk->clearFullRows();
}

int Grid::deadBlocksRemoved() {
	const vector<vector<Square*>>& squares = chunk->getSquares();
	int blocksRemoved = 0;

	for(int i = 0; i < (int)deadBlocks.size();) {
		bool blockExists = false;
		for(auto row : squares) {
			for(auto square : row) {
				if(square->uid == deadBlocks[i]->getUID()) {
					++i;
					blockExists = true; //There are still squares left
					break;
				}
			}
			if(blockExists) break;
		}

		if(!blockExists) {
			//Dead block has been completely removed
			blocksRemoved += pow(deadBlocks[i]->getCreationLevel() + 1, 2);

			delete deadBlocks[i];
			deadBlocks.erase(deadBlocks.begin()+i);
		}
	}

	return blocksRemoved;
}

bool Grid::isComplete() {
	return gridcomplete;
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
