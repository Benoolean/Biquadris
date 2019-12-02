#include "player.h"
using namespace std;

Player::Player(string source, int level)
  : grid(BlockGrid()), source(source), level(level), points(0) { }
