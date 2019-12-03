#include <string>
#include <vector>

#include "../headers/effect.h"
#include "../headers/blockgrid.h"
#include "../headers/biquadris.h"

class Player
{
	BlockGrid* grid;

	std::string source; //This allows a new stream to be opened once the end of either hase been reached
	std::vector<std::string> sequence;
	std::vector<std::vector<std::string>> sequenceProbabilities; // created with levelX.txt (custom chance drop)
	std::vector<std::string> customSequence; // created with fileXXX.txt (custom sequence mid game)
	int currentBlock;
	unsigned int turnNumber = 0;

	bool readcustomSequence = false;

	int level;
	int score;

	//These effects stack for each turn
	//When a user applies an effect, it is stacked on top of the next
	//grid. The current effect is set to the topmost effect, otherwise nullptr.
	//After every turn the effects are deleted.
	std::vector<Effect*> effects;
	Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

	std::vector<std::vector<Effect*>> levelEffects;

public:
	Player(std::string source, int level = 0);
	~Player();

	void blockSequenceProbabilitySetup();

	bool spawnNewBlock();
	bool setBlock(Block* newBlock);

	void addEffect(Biquadris::EffectType type);
	void addEffect(Effect* e);

	void addLevelEffect(Effect* e, int level);

	void setRandom();
	void setNotRandom(std::string source);

	int getCurrentLevel();

	void getNextBlock();

	void setNewLevel(int newLevel);

	Grid* currentBaseGrid(); //Ignores level effects
	Grid* currentGrid();

	friend class Level;
};
