#include "../headers/blockgrid.h"
#include <iostream>

using namespace std;

BlockGrid::BlockGrid() : Grid() { }

BlockGrid::~BlockGrid() { }

NextGrid::NextGrid(string block)
{
	// 4 x 4 grid
	this->update(block);
}

NextGrid::~NextGrid()
{
}

void NextGrid::clear()
{
	this->nextGrid.clear();
}

void NextGrid::update(std::string block)
{
	this->nextGrid.clear();

	Block nextblock = Block(*Biquadris::defaults[block]);

	Coordinate topleftCorner = nextblock.getTopLeftCornerWwithPadding();
	Coordinate bottomRightCorner = nextblock.getBottomRightCornerWwithPadding();

	int width = (int)(bottomRightCorner.x - topleftCorner.x) + 1;
	int height = (int)(bottomRightCorner.y - topleftCorner.y) + 1;

	int shiftx = topleftCorner.x;
	int shifty = topleftCorner.y;

	for (int rowcount = 0; rowcount < 4; rowcount++)
	{
		vector<string> row;
		this->nextGrid.push_back(row);

		for (int colcount = 0; colcount < 4; colcount++)
		{
			int squareposx = colcount + shiftx;
			int squareposy = rowcount + shifty;
			Square* square = nextblock.getSquareFromCoordinate(Coordinate{ squareposx, squareposy });

			string symbol = (square != nullptr) ? square->symbol : " ";

			this->nextGrid.at(rowcount).push_back(symbol);
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
	vector<string> row = this->nextGrid.at(rowcount);

	bool isEmpty = true;

	for (auto col : row)
	{
		isEmpty = isEmpty && (col == " ");
	}

	return isEmpty;
}

void NextGrid::printRow(int rowcount)
{
	vector<string> row = this->nextGrid.at(rowcount);
	
	if (!this->isRowEmpty(rowcount))
	{
		for (auto col : row)
		{
			cout << col;
		}
	}
}
