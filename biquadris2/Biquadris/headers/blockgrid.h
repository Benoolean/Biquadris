#ifndef BLOCKGRID_H
#define BLOCKGRID_H

#include <vector>
#include <string>
#include "grid.h"
#include "block.h"
#include "square.h"

class BlockGrid : public Grid
{
public:
	BlockGrid();
	~BlockGrid();
};


class NextGrid
{
	std::vector<std::vector<Square*>> nextGrid;
	std::vector<Block*> blockStorage;

public:
	NextGrid();
	~NextGrid();
	
	void reset();
	void update(std::string block);
	bool isRowEmpty(int rowcount);
	std::vector<std::vector<Square*>> getSquares();
};
#endif
