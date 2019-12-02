#include "player.h"
using namespace std;

Player::Player(string source, int level)
  : grid(new BlockGrid()), source(source), level(level), points(0) {
  // Get sequence!!!
}

Player::~Player() {
  delete grid;
}
