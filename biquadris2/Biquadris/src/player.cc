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
	: grid(new BlockGrid()), source(source), currentBlock(0), level(level), score(0), currentEffect(nullptr)
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

	// level random generator
	this->blockSequenceProbabilitySetup();
}

void Player::setLevel(int level) {

}

void Player::blockSequenceProbabilitySetup()
{
	this->sequenceProbabilities.clear();

	this->source = "media/levelinfo.txt";
	ifstream infoFile;
	infoFile.open(this->source);

	string input;

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
					this->addEffect(new Heavy{ this->currentGrid(), heavyMagnitude });
				}
				else if (effect == "blind")
				{
					this->addEffect(EffectType::BLIND);
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
}

bool Player::spawnNewBlock()
{
	Block* block = nullptr;

	if (this->level == 0)
	{
		block = new Block(*Biquadris::defaults[this->sequence[this->currentBlock]]);
		bool valid = this->grid->setActive(block);

		this->currentBlock = ((this->currentBlock + 1 >= (int)this->sequence.size()) ? 0 : this->currentBlock + 1);

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
		newEffect = new Heavy(this->currentGrid());
		break;
	case EffectType::BLIND:
		newEffect = new Blind(this->currentGrid());
		break;
	}
	effects.push_back(newEffect);
	currentEffect = newEffect;
}

void Player::addEffect(Effect* e) {
	effects.push_back(e);
	currentEffect = e;
}

Grid* Player::currentGrid() {
	if (currentEffect)
		return currentEffect;
	else
		return grid;
}
