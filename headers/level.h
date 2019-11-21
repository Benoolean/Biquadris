#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "grid.h"

#include <vector>
#include <string>

class Xwindow;

class Level {
  int level;

  Xwindow* window;
  bool enableGraphics;

  Grid* activeGrid;
  Grid grid1, grid2;

  std::vector<std::string> sequence1, sequence2; // Pushed from specified fstream, and stack popped every drop
  std::vector<std::string>* currentSequence;

  std::vector<Effect*> effects;
  Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

  void togglePlayer();

public:
  Level(int level = 0, bool window = nullptr, std::string source1, std::string source2);
  ~Level();

  void increaseLevel(); //Increases level by 1 up to 4
  void lowerLevel(); //Decreases level by 1 down to 0

  void changeActive(Block* newActive); //Will be used for force and after each drop

  bool validMove(Block);
};

#endif
