#include "../headers/player.h"

#include "../headers/heavy.h"
#include "../headers/blind.h"

#include <fstream>

using namespace std;
using namespace Biquadris;

Player::Player(string source, int level)
	: grid(new BlockGrid()), source(source), currentBlock(0), level(level), score(0), currentEffect(nullptr)
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

	for (auto effect : effects)
	{
		delete effect;
	}
}

bool Player::spawnNewBlock()
{
	Block* block = new Block(*Biquadris::defaults[this->sequence[this->currentBlock]]);
	bool valid = this->grid->setActive(block);

	this->currentBlock = ((this->currentBlock + 1 >= (int)this->sequence.size()) ? 0 : this->currentBlock + 1);

	return valid;
}

bool Player::setBlock(Block* newBlock) {
	bool valid = this->grid->setActive(newBlock);
	return valid;
}

void Player::addEffect(EffectType type) {
	Effect* newEffect = nullptr;
	switch(type) {
	case EffectType::HEAVY:
		newEffect = new Heavy(this->currentGrid());
		break;
	case EffectType::BLIND:
		newEffect = new Blind(this->currentGrid());
		break;
	}
	effects.push_back(newEffect);
	currentEffect = newEffect;
}

Grid* Player::currentGrid() {
	if (currentEffect)
		return currentEffect;
	else
		return grid;
}
