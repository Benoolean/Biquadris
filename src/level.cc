#include "level.h"
using namespace std;

Level::Level(const int level,
  const int numPlayers,
  std::vector<std::string> source,
  std::ostream* out, Xwindow* window)
    : level(level), out(out), window(window), currentPlayer(0),
      over(false), winner(-1) {

  if(this->level > 4) {
    print("Warning: level too high, 4 is the highest level.");
    print("Setting level to 4.");
    this->level = 4;
  }
  else if(this->level < 0) {
    print("Warning: level too low, 0 is the lowest level.");
    print("Setting level to 0.");
    this->level = 0;
  }

  for(int i = 0; i < numPlayers; i++) {
    players.push_back(new Player(source[i])); //Default initialize to "" src
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
  if(out) {
    (*out) << s << endl;
  }
}

Grid* Level::currentGrid() {
  if(currentEffect) return currentEffect;
  else return &(players[currentPlayer]->grid);
}

void Level::draw() {
  currentGrid()->draw(out, window);
}
