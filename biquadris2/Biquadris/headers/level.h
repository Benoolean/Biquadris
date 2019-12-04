#ifndef LEVEL_H
#define LEVEL_H

#include "biquadris.h"
#include "block.h"
#include "player.h"
#include "blockgrid.h"
#include "effect.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Xwindow;

class Level {
	Xwindow* window;

	std::vector<Player*> players;
	int currentPlayer;

	static int highScore;

	bool over; //True for over, false for not over
	bool tie;
	std::vector<int> tiedWith;
	unsigned int winner; // Undefined behaviour unless isOver flag is set

	void changePlayer(int player);

	void checkFullLine(); //Used to determine if there is a full line (also updates players' score)

	void print(std::string s);

public:
	Level(int level = 0,
		const int numPlayers = 2,
		bool withGraphics = true,
		std::vector<std::string> source = std::vector<std::string>());
	~Level();

	void StartGame();

	Player* getCurrentPlayer();
	Player* getNextPlayer();
	void nextPlayer();

	void decideWinner();
	bool isTie() const;

	void setGameOver();
	void restart();

	void blockDropped();
	void playerDone();
	bool spawnBlock();

	void increaseLevel(); //Increases level by 1 up to 4
	void decreaseLevel(); //Decreases level by 1 down to 0

	bool changeActive(Block* newActive); //Will be used for force and after each drop

	void sequenceCommands(std::string source);

	bool move(Biquadris::Direction direction);
	void rotateCClockwise();
	void rotateClockwise();

	void setRandom();
	void setNotRandom(std::string source);

	void promptEffect();

	bool isOver() const;
	int getWinner() const; //Returns -1 if isOver flag is not set
	static int getHighScore();

	void draw();

};

#endif
