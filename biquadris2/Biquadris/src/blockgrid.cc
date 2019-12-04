#include "../headers/blockgrid.h"
#include <iostream>

using namespace std;

BlockGrid::BlockGrid() : Grid() { }

BlockGrid::~BlockGrid() { }

NextGrid::NextGrid()
{
	//this->nextGrid = vector<vector<Square*>> (4);
	// 4 x 4 grid
	////this->update(block);

	for (int rowcount = 0; rowcount < 4; rowcount++)
	{
		vector<Square*> row;

		for (int colcount = 0; colcount < 4; colcount++)
		{
			row.push_back(nullptr);
		}

		this->nextGrid.push_back(row);
	}
}

NextGrid::~NextGrid()
{
}

void NextGrid::reset() 
{
	for (auto block : this->blockStorage)
	{
		delete block;
	}

	this->blockStorage.clear();

	for (auto& row : this->nextGrid)
	{
		for (auto& col : row)
		{
			col = nullptr;
		}
	}
}

void NextGrid::update(std::string block)
{
	this->reset();

	Block* nextblock = new Block(*Biquadris::defaults[block]);
	this->blockStorage.push_back(nextblock);

	Coordinate topleftCorner = nextblock->getTopLeftCornerWwithPadding();
	Coordinate bottomRightCorner = nextblock->getBottomRightCornerWwithPadding();

	int width = (int)(bottomRightCorner.x - topleftCorner.x) + 1;
	int height = (int)(bottomRightCorner.y - topleftCorner.y) + 1;

	int shiftx = topleftCorner.x;
	int shifty = topleftCorner.y;

	for (int rowcount = 0; rowcount < 4; rowcount++)
	{
		for (int colcount = 0; colcount < 4; colcount++)
		{
			int squareposx = colcount + shiftx;
			int squareposy = rowcount + shifty;
			Square* square = nextblock->getSquareFromCoordinate(Coordinate{ squareposx, squareposy });

			//string symbol = (square != nullptr) ? square->symbol : " ";
			this->nextGrid.at(rowcount).at(colcount)= square;
		}
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	printRow(i);
	//	cout << endl;
	//}
}

bool NextGrid::isRowEmpty(int rowcount)
{
	vector<Square*> row = this->nextGrid.at(rowcount);

	bool isEmpty = true;

	for (auto col : row)
	{
		isEmpty = isEmpty && (col == nullptr);
	}

	return isEmpty;
}

vector<vector<Square*>> NextGrid::getSquares()
{
	return this->nextGrid;
}
