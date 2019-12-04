#include "../headers/level.h"
#include "../headers/square.h"
#include <fstream>
#include "../headers/window.h"

using namespace std;
using namespace Biquadris;

int Level::highScore = 0;

const int WINDOW_WIDTH = 720,
					WINDOW_HEIGHT = 720,
					GRID_WIDTH_PX = 300;

Level::Level(int level, const int numPlayers, bool withGraphics, std::vector<std::string> source)
	: currentPlayer(0), over(false), tie(false), winner(-1)
{
	if (level > MAX_LEVEL)
	{
		print("Warning: level too high, 4 is the highest level.");
		print("Setting level to 4.");
		level = MAX_LEVEL;
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

	if(withGraphics) {
		window = new Xwindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

Level::~Level()
{
	delete window;

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
			if (this->getCurrentPlayer()->grid->isActive())
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
			this->rotateClockwise();
		}
		else if (cmd == "levelup")
		{
			this->increaseLevel();
		}
		else if (cmd == "leveldown")
		{
			this->decreaseLevel();
		}
		else if (cmd == "norandom")
		{
			string fileSource = "";
			cin >> fileSource;

			this->setNotRandom(fileSource);
		}
		else if (cmd == "restart")
		{
			this->restart();
		}
		else if (cmd == "sequence")
		{
			string fileSource = "";
			cin >> fileSource;

			this->sequenceCommands(fileSource);
		}
		this->draw();
	}
}

void Level::setRandom()
{
	Player* player = this->getCurrentPlayer();
	player->setRandom();
}

void Level::setNotRandom(std::string source)
{
	Player* player = this->getCurrentPlayer();
	player->setNotRandom(source);
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
			if (defaults.count(in))
			{
				Player* next = this->getNextPlayer();
				if (!next->grid->isComplete() && !next->setBlock(new Block(*defaults[in])))
				{
					playerDone();
				}
				return;
			}
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
	int nextPlayer = ((currentPlayer + 1 >= (int)players.size()) ? 0 : currentPlayer + 1);
	int i = 1;
	while(players[nextPlayer]->grid->isComplete()) {
		//If there has been a full rotation of characters
		//and all of them are complete, end the game.
		if(i >= players.size()) {
			this->setGameOver(); //***Set the game to over
			break;
		}

		nextPlayer = ((nextPlayer + 1 >= (int)players.size()) ? 0 : nextPlayer + 1);
		++i;
	}
	currentPlayer = nextPlayer;
}

void Level::blockDropped()
{
	Player* current = this->getCurrentPlayer();
	int rowsRemoved = current->currentGrid()->checkRowCompleteness();
	current->score += current->grid->deadBlocksRemoved();
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

void Level::increaseLevel()
{
	Player* currentPlayer = this->getCurrentPlayer();
	int currentPlayerLevel = currentPlayer->getCurrentLevel();
	if(currentPlayerLevel < MAX_LEVEL) {
		this->getCurrentPlayer()->setNewLevel(++currentPlayerLevel);
	}
}

void Level::decreaseLevel() {
	Player* currentPlayer = this->getCurrentPlayer();
	int currentPlayerLevel = currentPlayer->getCurrentLevel();
	if(currentPlayerLevel > 0) {
		this->getCurrentPlayer()->setNewLevel(--currentPlayerLevel);
	}
}

// constants
string GRID_SEPERATION_SPACE = "     ";
string NEXT_SEPERATION_SPACE = "          ";
string NEXTBLOCK_SEPERATION_SPACE = "            ";
string GRID_BAR_SEPERATOR = "-----------";
int GRIDBORDERWIDTH = 11 + 5 + 11;
int GRIDCMDCLEAR = 10;

void Level::draw()
{
	for (int i = 0; i < GRIDCMDCLEAR; i++)
	{
		cout << endl;
	}

	for (int i = 0; i < GRIDBORDERWIDTH; i++)
	{
		char c = '#';
		cout << c;
	}
	cout << endl;

	/*========= print level and score =========*/

	// todo dynamic spacing based on score

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
				cout << s.symbol;
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

	cout << "Next: "  << NEXT_SEPERATION_SPACE << "Next: "<< endl;
	for (int i = 0; i < 4; i++)
	{
		for (auto player : this->players)
		{
			vector<Square*> row = player->nextGrid->getSquares().at(i);

			for (auto col : row)
			{
				if (col == nullptr)
				{
					cout << " ";
				}
				else
				{
					cout << col->symbol;
				}
			}
			cout << NEXTBLOCK_SEPERATION_SPACE;
		}
		cout << endl;
	}

	for (int i = 0; i < GRIDBORDERWIDTH; i++)
	{
		char c = '#';
		cout << c;
	}
	cout << endl << "Enter next command: ";

	if(this->window) {
		int separationPixels = (WINDOW_WIDTH - (this->players.size() * GRID_WIDTH_PX)) / (this->players.size() + 1);
		float squareWidth = GRID_WIDTH_PX / GridInfo::GRID_WIDTH;
		int GRID_HEIGHT_PX = squareWidth * GridInfo::GRID_HEIGHT;

		window->fillRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		for(int i = 0; i < (int)players.size(); i++) {
			int paddingLeft = ((i+1) * separationPixels) + (i*GRID_WIDTH_PX);
			window->fillRectangle(paddingLeft-1, 0, GRID_WIDTH_PX+2, WINDOW_HEIGHT);
			window->fillRectangle(paddingLeft, 1, GRID_WIDTH_PX, WINDOW_HEIGHT-2, 0);

			window->drawBigString(paddingLeft + 10, 20, "Level: " + to_string(players[i]->level));
			window->drawBigString(paddingLeft + 10, 39, "Score: " + to_string(players[i]->score));

			window->fillRectangle(paddingLeft, 49, GRID_WIDTH_PX, GRID_HEIGHT_PX+2); //Create top and bottom border

			vector<vector<Square>> chunk = players[i]->currentGrid()->getPlayerChunk();
			for(auto row : chunk) {
				for(auto square : row) {
					if(square.status != SquareStatus::INACTIVE) {
						window->fillRectangle(paddingLeft + (square.position.x * squareWidth),
																50 + (square.position.y * squareWidth),
																squareWidth, squareWidth, square.colour);
					}
				}
			}

			window->drawBigString(paddingLeft + 10, 75 + GRID_HEIGHT_PX, "Next:");

			vector<vector<Square*>> next = players[i]->nextGrid->getSquares();
			window->fillRectangle(paddingLeft, 89 + GRID_HEIGHT_PX, (squareWidth * next[0].size()), (squareWidth * next.size()) + 2);

			for(auto row : next) {
				for(auto square : row) {
					if(square) {
						if(square->status != SquareStatus::INACTIVE) {
							window->fillRectangle(paddingLeft + (square->position.x * squareWidth),
																	90 + GRID_HEIGHT_PX + (square->position.y * squareWidth),
																	squareWidth, squareWidth, square->colour);
						}
					}
				}
			}
		}
	}
}

void Level::decideWinner() {
	int winner = 0;
	vector<int> tiedWith({0});
	for(int i = 1; i < players.size(); i++) {
		int scoreI = players[i]->score, scoreW = players[winner]->score;
		if(scoreI == scoreW) {
			tiedWith.push_back(i);
		}
		else if(scoreI > scoreW) {
			winner = i;

			tiedWith.clear();
			tiedWith.push_back(winner);
		}
	}

	if((int)tiedWith.size() > 1) {
		this->tie = true;
		this->tiedWith.swap(tiedWith);
	}
	this->winner = winner;
}

bool Level::isTie() const {
	return this->tie;
}

void Level::setGameOver()
{
	this->over = true;
	this->decideWinner();

	if(this->window) {
		window->fillRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
		window->fillRectangle(20, 20, WINDOW_WIDTH-40, WINDOW_HEIGHT-40);

		window->drawBigString(30, 40, "Game over!", 0);
		window->drawBigString(30, 60, "The high score is: " + to_string(highScore), 0);

		int nextY = 100;

		if(this->isTie()) {
			window->drawBigString(30, 80, "It was a tie! The winners are: ", 0);
			for(int i = 0; i < (int)tiedWith.size(); i++) {
				nextY += 15;
				window->drawBigString(30, 95 + i*15, "Player " + to_string(tiedWith[i] + 1), 0);
			}
			nextY += 5;
		}
		else {
			window->drawBigString(30, 80, "The winner is: Player " + to_string(winner+1), 0);
		}

		int _nextY = nextY;

		for(int i = 0 ; i < players.size(); i++) {
			window->drawBigString(30, nextY + i*15, "Player " + to_string(i+1) + " finished with: " + to_string(players[i]->score), 0);
			_nextY += 15;
		}
		_nextY += 20;

		window->drawBigString(30, _nextY, "Type 'restart' to start a new game", 0);
	}

	cout << endl << endl << endl;
	cout << GRID_BAR_SEPERATOR << endl;

	cout << "Game over!" << endl;
	cout << "The high score is: " << highScore << endl;

	if(this->isTie()) {
		cout << "It was a tie! The winners are: ";
		for(int i = 0; i < (int)tiedWith.size(); i++) {
			cout << "Player " << tiedWith[i]+1;
			if(i+1 < tiedWith.size()) {
				cout << ", ";
			}
		}
		cout << endl;
	}
	else {
		cout << "The winner is: Player " << winner << endl;
	}

	cout << GRID_BAR_SEPERATOR << endl;

	for(int i = 0 ; i < players.size(); i++) {
		cout << "Player " << i+1 << " finished with: " <<  players[i]->score << endl;
	}

	cout << GRID_BAR_SEPERATOR << endl;

	cout << "Type 'restart' to start a new game: " << endl;

	string in = "";
	while(in != "restart") {
		cin >> in;
	}

	this->restart();
}

void Level::restart()
{
	cout << "Restarting game..." << endl;
	for (auto player : this->players) {
		player->reset();
	}

	this->over = false;
	this->currentPlayer = 0;
}

void Level::rotateCClockwise()
{
	Player* player = this->getCurrentPlayer();
	return player->grid->rotateCClockwise();
}

void Level::rotateClockwise()
{
	Player* player = this->getCurrentPlayer();
	return player->grid->rotateClockwise();
}

bool Level::move(Biquadris::Direction direction)
{
	Player* player = this->getCurrentPlayer();
	return player->currentGrid()->move(direction);
}

void Level::sequenceCommands(string source)
{
	//Player* player = this->getCurrentPlayer();

	string filesource = "media/" + source;
	ifstream filestream;
	filestream.open(filesource);

	string cmd;
	while (filestream >> cmd)
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
			if (this->getCurrentPlayer()->grid->isActive())
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
			this->rotateClockwise();
		}
		else if (cmd == "levelup")
		{
			this->increaseLevel();
		}
		else if (cmd == "leveldown")
		{
			this->decreaseLevel();
		}
		else if (cmd == "norandom")
		{
			string fileSource = "";
			cin >> fileSource;

			this->setNotRandom(fileSource);
		}
		else if (cmd == "restart")
		{
			this->restart();
		}
		//else if (cmd == "sequence")
		//{
		//	string fileSource = "";
		//	cin >> fileSource;

		//	this->sequenceCommands(fileSource);
		//}
	}

	this->draw();
}
