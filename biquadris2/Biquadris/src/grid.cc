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
	const vector<Square*>& bSquares = newActive->getSquares();
	for (int i = 0; i < bSquares.size(); i++)
	{
		//Check if the new square contacts any of the existing squares
		/*if (chunk->getSquares()[bSquares[i]->position.x + (bSquares[i]->position.y * Biquadris::GridInfo::GRID_WIDTH)]->status == SquareStatus::ACTIVE)
		{
			gridcomplete = true;
			return false;
		}*/
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

vector<Square> Grid::getGrid()
{
	vector<Square> grid;
	const vector<vector<Square*>>& chunkSquares = chunk->getSquares();

	/*for (int i = 0; i < chunkSquares.size(); i++)
	{
		grid.push_back(*chunkSquares[i]);
	}
*/
	return grid;
}
