#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "grid.h"

#include <vector>

class Level {
  int level;

  Grid* activeGrid;
  Grid grid1, grid2;

public:
  Level(int level = 0);

  void increaseLevel(); //Increases level by 1 up to 4
  void lowerLevel(); //Decreases level by 1 down to 0

  bool validMove(Block);

  bool shiftX();
  bool shiftY();
};

#endif
