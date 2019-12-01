#include "player.h"
using namespace std;

Player::Player(string source)
  : grid(BlockGrid()), source(source), points(0) { }
