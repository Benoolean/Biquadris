#include "../headers/level.h"
#include "../headers/square.h"

using namespace std;
using namespace Biquadris;

int Level::highScore = 0;

Level::Level(int level, const int numPlayers, bool withGraphics, std::vector<std::string> source)
	: currentPlayer(0), over(false), winner(-1)
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
	for (auto player : players)
	{
		delete player;
	}
}

//Helper function that returns x to the power of y
int power(int x, unsigned int y)
{
	int current = ((y == 0) ? 1 : x);

	for (int i = 0; i < (int)y; i++)
	{
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
			//Blocks can drop when moving horizontally if the heavy effect
			//is in place
			if (!this->move(Direction::RIGHT))
			{
				this->blockDropped();
			}
		}
		else if (cmd == "left")
		{
			if (!this->move(Direction::LEFT))
			{
				this->blockDropped();
			}
		}
		else if (cmd == "down")
		{
			if (!this->move(Direction::DOWN))
			{ //Block died
				this->blockDropped();
			}
		}
		else if (cmd == "drop")
		{
			if (this->getCurrentPlayer()->currentGrid()->isActive())
			{
				while (this->move(Direction::DOWN)) {}
				blockDropped();
			}
		}
		else if (cmd == "counterclockwise")
		{
			this->rotateCClockwise();
		}
		else if (cmd == "clockwise")
		{
			this->rotateCClockwise();
		}

		this->draw();
	}
}

void Level::promptEffect()
{
	string in;
	cout << "Choose debuff: blind, heavy, or force [block]" << endl;

	while (cin >> in)
	{
		if (in == "blind")
		{
			this->getNextPlayer()->addEffect(EffectType::BLIND);
			return;
		}
		else if (in == "heavy")
		{
			this->getNextPlayer()->addEffect(EffectType::HEAVY);
			return;
		}
		else if (in == "force")
		{
			cin >> in;
			if (defaults.find(in) != defaults.end())
			{
				if (!this->getNextPlayer()->setBlock(new Block(*defaults[in])))
				{
					playerDone();
				}
			}
			return;
		}
		cout << "Choose debuff: blind, heavy, or force [block]" << endl;
		cout << "Invalid input. Try again." << endl;
	}
}

void Level::print(string s) { cout << s << endl; }

Player* Level::getCurrentPlayer()
{
	return this->players.at(this->currentPlayer);
}

Player* Level::getNextPlayer()
{
	int nextPlayer = ((currentPlayer + 1 >= (int)players.size()) ? 0 : currentPlayer + 1);
	return this->players.at(nextPlayer);
}

void Level::nextPlayer() {
	int nextPlayer = ((currentPlayer+1 >= (int) players.size()) ? 0 : currentPlayer+1);
	int i = 0;
	while(players[nextPlayer]->currentGrid()->isComplete()) {
			//If there has been a full rotation of characters
			//and all of them are complete, end the game.
			if(i > players.size()) {
				this->setGameOver(); //***Set the game to over
				break;
			}

		nextPlayer = ((currentPlayer + 1 >= (int)players.size()) ? 0 : currentPlayer + 1);
		++i;
	}
	currentPlayer = nextPlayer;
}

void Level::setGameOver()
{
	this->over = true;
	cout << "Game over!" << endl;
}

void Level::blockDropped()
{
	Player* current = this->getCurrentPlayer();
	int rowsRemoved = current->currentGrid()->checkRowCompleteness();
	if (rowsRemoved)
	{ //If any rows were cleared update players score
		current->score += power(current->level + rowsRemoved, 2);
		if (current->score > highScore) highScore = current->score;

		if (rowsRemoved >= 2) this->promptEffect();
		//When an entire block is removed, score += (levelatcreation + 1)^2
	}

	if (!this->spawnBlock())
	{
		this->playerDone();
	}

	this->nextPlayer();
}

void Level::playerDone()
{
	cout << "Player is out!" << endl;
}

bool Level::spawnBlock()
{
	Player* currentPlayer = this->getCurrentPlayer();
	return currentPlayer->spawnNewBlock();
}

// constants
string GRID_SEPERATION_SPACE = "     ";
string GRID_BAR_SEPERATOR = "-----------";

void Level::draw()
{
	/*========= print level and score =========*/

	// todo dynanmic spacing based on score

	for (int i = 0; i < (int)this->players.size(); i++)
	{
		cout << "Level:"
			<< "    " << players[i]->level;
		if (i + 1 != (int)this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	for (int i = 0; i < (int)this->players.size(); i++)
	{
		cout << "Score:"
			<< "    " << players[i]->score;
		if (i + 1 != (int)this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print grid =========*/

	// grid bar
	for (int i = 0; i < (int)this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != (int)this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	// Get all copies of player chunks now, to avoid
	// unnecessary copying
	vector<vector<vector<Square>>> playersSquares;
	for (auto player : this->players)
	{
		playersSquares.push_back(player->currentGrid()->getPlayerChunk());
	}

	// print each row by player count
	for (int rowcount = 0; rowcount < (int)GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int numPlayer = 0; numPlayer < (int)players.size(); numPlayer++)
		{
			for (int colcount = 0; colcount < GridInfo::GRID_WIDTH; colcount++)
			{
				Square s = playersSquares[numPlayer].at(rowcount).at(colcount);
				if (s.status == SquareStatus::DEAD)
				{
					cout << (char)219;
				}
				else
				{
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
	for (int i = 0; i < (int)this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != (int)this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print next=========*/

	cout << "Next: " << endl;
}

void Level::rotateCClockwise()
{
	Player* player = this->getCurrentPlayer();
	return player->currentGrid()->rotateCClockwise();
}

bool Level::move(Biquadris::Direction direction)
{
	Player* player = this->getCurrentPlayer();
	return player->currentGrid()->move(direction);
}
