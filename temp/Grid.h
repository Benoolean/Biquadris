#pragma once
#include <vector>
#include "Block.h"
#include "Square.h"

enum class GridInfo { GRID_HEIGHT = 15, GRID_WIDTH = 11 };

class Grid
{
	std::vector<std::vector<Square>> squares;

public:
	Block* activeBlock;
	Grid();
	~Grid();
	std::vector<Square>& getRow(int rowNum);
	void move(Direction direction);
	//void drop();

	void UpdateSquare(Coordinate position, Square& square, SquareStatus newSquareStatus);
	void ActiveBlockUpdate(SquareStatus squareStatus);
};