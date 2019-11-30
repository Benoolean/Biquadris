#pragma once
#include <string>
#include "Grid.h"
#include "Square.h"

// enums
enum class LevelInfo { MAX_PLAYERS = 2 };

class Level 
{
	bool isPlayerOneTurn = true;
	int level = 0;
	int seed = 0;
	std::string file1 = "sequence1.txt";
	std::string file2 = "sequence2.txt";

	Grid* playerOneGrid;
	Grid* playerTwoGrid;

public:
	void StartGame();
	void printGrid();

	void SpawnBlock();
	void move(Direction direction);
};
