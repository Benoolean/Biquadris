#include "level.h"
#include "square.h"
using namespace std;
using namespace Biquadris;

Level::Level(int level,
  const int numPlayers,
  bool withGraphics,
  std::vector<std::string> source)
    : currentPlayer(0),
      over(false), winner(-1),
      currentEffect(nullptr) {

  if(level > 4) {
    print("Warning: level too high, 4 is the highest level.");
    print("Setting level to 4.");
    level = 4;
  }
  else if(level < 0) {
    print("Warning: level too low, 0 is the lowest level.");
    print("Setting level to 0.");
    level = 0;
  }

  for(int i = 0; i < numPlayers; i++) {
    players.push_back(new Player(((source.size() > i) ? source[i] : ""), level)); //Default initialize to "" src
  }
}

Level::~Level() {
  for(auto effect : effects) {
    delete effect;
  }

  for(auto player : players) {
    delete player;
  }
}

void Level::print(string s) {
  cout << s << endl;
}

Grid* Level::currentGrid() {
  if(currentEffect) return currentEffect;
  else return players[currentPlayer]->grid;
}

// constants
string GRID_SEPERATION_SPACE = "    ";
string GRID_BAR_SEPERATOR = "-----------";

void Level::draw() {
  /*========= print level and score =========*/

	// todo dynanmic spacing based on score

  for(int i = 0; i < this->players.size(); i++) {
      cout << "Level:" << "   " << players[i]->level;
      if(i + 1 != this->players.size()) {
        cout << GRID_SEPERATION_SPACE;
      }
  }
  cout << endl;

  for(int i = 0; i < this->players.size(); i++) {
      cout << "Score:" << "   " << players[i]->points;
      if(i + 1 != this->players.size()) {
        cout << GRID_SEPERATION_SPACE;
      }
  }
  cout << endl;

	/*========= print grid =========*/

  for(int i = 0; i < this->players.size(); i++) {
  	cout << GRID_BAR_SEPERATOR;
    if(i + 1 != this->players.size()) {
      cout << GRID_SEPERATION_SPACE;
    }
  }
  cout << endl;

  vector<vector<Square>> playerSquares;

  for(int i = 0; i < this->players.size(); i++) {
    playerSquares.push_back(this->players[i]->grid->getGrid());
  }

	// print each row by player count
	for (int rowcount = 0; rowcount < (int) GridInfo::GRID_HEIGHT; rowcount++)
	{
		for (int playerNum = 0; playerNum < players.size(); playerNum++)
		{
      for(int i = 0; i < GridInfo::GRID_WIDTH; i++) {
        cout << playerSquares[playerNum][(rowcount * GridInfo::GRID_WIDTH) + i].symbol;
      }
			cout << GRID_SEPERATION_SPACE;
		}

		cout << endl;
	}

	cout << GRID_BAR_SEPERATOR << endl;

	/*========= print next=========*/

	cout << "Next:" << endl;
}
