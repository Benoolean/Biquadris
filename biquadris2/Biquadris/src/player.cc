#include "../headers/player.h"

#include "../headers/heavy.h"
#include "../headers/blind.h"

#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace Biquadris;

int MAX_LEVEL;

Player::Player(string source, int level)
	: grid(new BlockGrid()), source(source), currentBlock(0), level(level), score(0),
	currentEffect(nullptr), levelEffects(4)

{
	// default level
	ifstream sourcefile;
	sourcefile.open(source);

	string block;
	while (sourcefile >> block)
	{
		sequence.push_back(block);
	}

	sourcefile.close();

	// next grid setup
	this->nextGrid = new NextGrid{ this->getNextBlock() };

	// level random generator
	this->blockSequenceProbabilitySetup();
}

void Player::blockSequenceProbabilitySetup()
{
	this->sequenceProbabilities.clear();

	this->source = "media/levelinfo.txt";
	ifstream infoFile;
	infoFile.open(this->source);

	string input;

	int levelIndex = 1;

	while (infoFile >> input)
	{
		ifstream levelFile;

		string levelFileSource = "media/" + input;
		levelFile.open(levelFileSource);

		string levelDetail = "";
		vector<string> levelSpawnRate;

		while (getline(levelFile, levelDetail))
		{
			istringstream ss(levelDetail);
			string stringInput = "";
			int blockChances = 0;

			ss >> stringInput;

			if (stringInput == "EFFECT")
			{
				string effect = "";
				ss >> effect;

				if (effect == "heavy")
				{
					int heavyMagnitude;
					ss >> heavyMagnitude;
					this->addLevelEffect(new Heavy{ nullptr, heavyMagnitude }, levelIndex);
				}
				else if (effect == "blind")
				{
					this->addLevelEffect(new Blind(nullptr), levelIndex);
				}
			}
			else
			{
				ss >> blockChances;

				for (int i = 0; i < blockChances; i++)
				{
					levelSpawnRate.push_back(stringInput);
				}
			}
		}

		this->sequenceProbabilities.push_back(levelSpawnRate);

		++levelIndex;

		levelFile.close();
	}

	infoFile.close();

	return;
}

Player::~Player()
{
	delete this->grid;

	for (auto effect : effects)
	{
		delete effect;
	}

	for (auto effects : levelEffects)
	{
		for (auto effect : effects)
		{
			delete effect;
		}
	}
}

bool Player::spawnNewBlock()
{
	Block* block = nullptr;

	if (this->readcustomSequence) // check if we are currently not random and is reading from a different sequence
	{
		block = new Block(*Biquadris::defaults[this->customSequence[this->currentBlock]]);
		bool valid = this->grid->setActive(block);

		this->currentBlock = ((this->currentBlock + 1 >= (int)this->customSequence.size()) ? 0 : this->currentBlock + 1);
		this->nextGrid->update(this->getNextBlock());
		return valid;
	}
	else if (this->level == 0)
	{
		block = new Block(*Biquadris::defaults[this->sequence[this->currentBlock]]);
		bool valid = this->grid->setActive(block);

		this->currentBlock = ((this->currentBlock + 1 >= (int)this->sequence.size()) ? 0 : this->currentBlock + 1);
		this->nextGrid->update(this->getNextBlock());
		return valid;
	}
	else
	{
		int sequenceIndex = this->level - 1;
		vector<string> levelSequence = this->sequenceProbabilities.at(sequenceIndex);

		int lower = 0;
		int upper = levelSequence.size() - 1;

		srand((unsigned)Biquadris::seed + this->turnNumber);

		int random = rand() % (upper + 1 - lower) + lower;
		string test = levelSequence.at(random);
		block = new Block(*Biquadris::defaults[levelSequence.at(random)]);

		bool valid = this->grid->setActive(block);

		turnNumber++;

		this->nextGrid->update(this->getNextBlock());
		return valid;
	}
}

bool Player::setBlock(Block* newBlock)
{
	bool valid = this->grid->setActive(newBlock);
	return valid;
}

void Player::addEffect(EffectType type)
{
	Effect* newEffect = nullptr;
	switch (type)
	{
	case EffectType::HEAVY:
		newEffect = new Heavy(this->currentBaseGrid());
		break;
	case EffectType::BLIND:
		newEffect = new Blind(this->currentBaseGrid());
		break;
	}
	effects.push_back(newEffect);
	currentEffect = newEffect;
}

void Player::addEffect(Effect* e) {
	effects.push_back(e);
	currentEffect = e;
}

#include <iostream>

void Player::addLevelEffect(Effect* e, int level) {
	if(levelEffects.at(level).size()) {
		e->setComponent(levelEffects.at(level).at(levelEffects[level].size()-1)); //Set the component to the topmost level effect
	}
	levelEffects.at(level).push_back(e);
}

void Player::setRandom()
{
	this->customSequence.clear();
	this->readcustomSequence = false;
}

void Player::setNotRandom(std::string source)
{
	this->customSequence.clear();
	this->currentBlock = 0;

	this->source = "media/" + source;
	ifstream filestream;
	filestream.open(this->source);

	string input;
	while (filestream >> input)
	{
		customSequence.push_back(input);
	}

	this->readcustomSequence = true;
}

int Player::getCurrentLevel()
{
	return this->level;
}

std::vector<std::string> Player::getCurrentSequence()
{
	return (this->readcustomSequence) ? this->customSequence : ((this->level == 0) ? this->sequence : this->sequenceProbabilities.at(this->level));
}

string Player::getNextBlock()
{
	vector<string> currentSquence;
	
	// get the current sequence;
	currentSquence = (this->readcustomSequence) ? this->customSequence : ((this->level == 0) ? this->sequence : this->sequenceProbabilities.at(this->level));

	int sequenceSize = currentSquence.size();
	
	if (this->currentBlock >= sequenceSize)
	{
		return currentSquence.at(0);
	}
	else
	{
		return currentSquence.at(currentBlock);
	}
}

void Player::setNewLevel(int newLevel)
{
	this->level = newLevel;
}

Grid* Player::currentBaseGrid() {
	if (currentEffect)
		return currentEffect;
	else
		return grid;
}

Grid* Player::currentGrid() {
	Grid* base = this->currentBaseGrid();
	Grid* top = base;
	if(levelEffects.at(level).size()) {
		levelEffects[level][0]->setComponent(base);
		top = levelEffects.at(level).at(levelEffects[level].size()-1); //Get the topmost level effect
	}
	return top;
}
