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


class NextGrid : public Grid
{
	std::vector<std::vector<std::string>> nextGrid;
public:
	NextGrid(std::string block);
	~NextGrid();
	
	void clear();
	void update(std::string block);
	bool isRowEmpty(int rowcount);
	void printRow(int rowcount);
};
#endif
