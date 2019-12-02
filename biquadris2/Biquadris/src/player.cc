#include "../headers/player.h"
#include <fstream>
using namespace std;

Player::Player(string source, int level)
	: grid(new BlockGrid()), source(source), currentBlock(0), level(level), points(0)
{
	ifstream sourcefile;
	sourcefile.open(source);

	string block;
	while (sourcefile >> block)
	{
		sequence.push_back(block);
	}

	sourcefile.close();
}

Player::~Player()
{
	delete this->grid;
}

void Player::spawnNewBlock()
{
	Block* block = new Block(*Biquadris::defaults[this->sequence[this->currentBlock]]);
	this->grid->setActive(block);

	this->currentBlock++;
}
