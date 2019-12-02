#include "../headers/level.h"
#include "../headers/square.h"

using namespace std;
using namespace Biquadris;

Level::Level(int level, const int numPlayers, bool withGraphics, std::vector<std::string> source)
	: currentPlayer(0), over(false), winner(-1), currentEffect(nullptr)
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
		players.push_back(new Player(((source.size() > i) ? source[i] : ""),
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
			this->move(Direction::DOWN);
		}
		this->draw();
	}
}

void Level::print(string s) { cout << s << endl; }

Player* Level::getCurrentPlayer()
{
	return this->players.at(this->currentPlayer);
}

void Level::spawnBlock()
{
	Player* currentPlayer = this->getCurrentPlayer();

	currentPlayer->spawnNewBlock();
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

	for (int i = 0; i < this->players.size(); i++)
	{
		cout << "Level:"
			<< "   " << players[i]->level;
		if (i + 1 != this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	for (int i = 0; i < this->players.size(); i++)
	{
		cout << "Score:"
			<< "   " << players[i]->points;
		if (i + 1 != this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print grid =========*/

	// grid bar
	for (int i = 0; i < this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != this->players.size())
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
	for (int i = 0; i < this->players.size(); i++)
	{
		cout << GRID_BAR_SEPERATOR;
		if (i + 1 != this->players.size())
		{
			cout << GRID_SEPERATION_SPACE;
		}
	}
	cout << endl;

	/*========= print next=========*/

	cout << "Next: " << endl;
}

void Level::move(Biquadris::Direction direction)
{
	Player* player = this->getCurrentPlayer();

	player->grid->move(direction);
}
