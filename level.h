#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "grid.h"

#include <vector>

class Xwindow;

class Level {
  int level;

  Xwindow* window;
  bool enableGraphics;

  Grid* activeGrid;
  Grid grid1, grid2;

  vector<Effect*> effects;
  Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

public:
  Level(int level = 0, bool window = nullptr);
  ~Level();

  void increaseLevel(); //Increases level by 1 up to 4
  void lowerLevel(); //Decreases level by 1 down to 0

  bool validMove(Block);
};

#endif
