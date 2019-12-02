#include "../headers/level.h"
#include "../headers/square.h"

using namespace std;
using namespace Biquadris;

Level::Level(int level, const int numPlayers, bool withGraphics, std::vector<std::string> source)
	: currentPlayer(0), currentEffect(nullptr), over(false), winner(-1)
{
	if (level > 4)
	{
		print("Warning: level too high, 4 is the highest level.");
		print("Setting level to 4.");
		level = 4;
	}
	else if (level < 0)
	{
		print("Warning: level too low, 0 is the lowest level.");
		print("Setting level to 0.");
		level = 0;
	}

	for (int i = 0; i < numPlayers; i++)
	{
		players.push_back(new Player(((source.size() > (int) i) ? source[i] : ""),
			level));  // Default initialize to "" src
	}
}

Level::~Level()
{
	for (auto effect : effects)
	{
		delete effect;
	}

	for (auto player : players)
	{
		delete player;
	}
}

//Helper function that returns x to the power of y
int power(int x, unsigned int y) {
	int current = ((y == 0) ? 1 : x);

	for(int i = 0; i < (int)y; i++) {
		current *= x;
	}

	return current;
}

void Level::StartGame()
{
	string cmd = "";

	// spawn block for all players
	for (auto player : this->players)
	{
		player->spawnNewBlock();
	}

	this->draw();

	while (cin >> cmd)
	{
		if (cmd == "right")
		{
			this->move(Direction::RIGHT);
		}
		else if(cmd == "left")
		{
			this->move(Direction::LEFT);
		}
		else if(cmd == "down")
		{
			if(!this->move(Direction::DOWN)) { //Block died
				this->blockDropped();
			}
		}
		else if(cmd == "drop") {
			if(this->getCurrentPlayer()->grid->isActive()) {
				while(this->move(Direction::DOWN)) {}
				blockDropped();
			}
		}
		this->draw();
	}
}

void Level::print(string s) { cout << s << endl; }

Player* Level::getCurrentPlayer()
{
	return this->players.at(this->currentPlayer);
}

void Level::blockDropped() {
	Player* current = this->getCurrentPlayer();
	int rowsRemoved = current->grid->checkRowCompleteness();
	if(rowsRemoved) { //If any rows were cleared update players score
		current->score += power(current->level + rowsRemoved, 2);
		//When an entire block is removed, score += (levelatcreation + 1)^2
	}

	if(this->spawnBlock()) {
			//Switch player
	}
	else { //Player 1 is out!
		cout << "Player 1 is out!" << endl;
	}
}

bool Level::spawnBlock()
{
	Player* currentPlayer = this->getCurrentPlayer();
	return currentPlayer->spawnNewBlock();
}

Grid* Level::currentGrid()
{
	if (currentEffect)
		return currentEffect;
	else
		return players[currentPlayer]->grid;
}

// constants
string GRID_SEPERATION_SPACE = "    ";
string GRID_BAR_SEPERATOR = "-----------";

void Level::draw()
{
	/*========= print level and score =========*/

	// todo dynanmic spacing based on score

	for (int i = 0; i < (int) this->players.size(); i++)
	{
		cout << "Level:"
			<< "   " << players[i]->level;
		if (i + 1 != (int) this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	for (int i = 0; i < (int) this->players.size(); i++)
	{
		cout << "Score:"
			<< "   " << players[i]->score;
		if (i + 1 != (int) this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print grid =========*/

	// grid bar
	for (int i = 0; i < (int) this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != (int) this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	// print each row by player count

	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (auto player : this->players)
		{
			for (int colcount = 0; colcount < GridInfo::GRID_WIDTH; colcount++)
			{
				Square s = player->grid->getPlayerChunk().at(rowcount).at(colcount);
				if(s.status == SquareStatus::DEAD) {
					cout << (char)219;
				}
				else {
					cout << s.symbol;
				}

				/*cout << playerSquares[playerNum][(rowcount * GridInfo::GRID_WIDTH) + i]
					.symbol;*/
			}

			cout << GRID_SEPERATION_SPACE;
		}

		cout << endl;
	}

	// grid bar
	for (int i = 0; i < (int) this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != (int) this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print next=========*/

	cout << "Next: " << endl;
}

bool Level::move(Biquadris::Direction direction)
{
	Player* player = this->getCurrentPlayer();
	return player->grid->move(direction);
}
