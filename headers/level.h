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

  std::string source1, source2; //This allows a new stream to be opened once the end of either hase been reached
  std::vector<std::string> sequence1, sequence2; // Pushed from specified fstream, and stack popped every drop
  std::vector<std::string>* currentSequence;

  std::vector<Effect*> effects;
  Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

  void togglePlayer();

  bool isOver;
  unsigned int winner; // Undefined behabiour unless isOver flag is set

public:
  Level(int level = 0, bool window = nullptr, std::string source1, std::string source2);
  ~Level();

  void increaseLevel(); //Increases level by 1 up to 4
  void lowerLevel(); //Decreases level by 1 down to 0

  bool changeActive(Block* newActive); //Will be used for force and after each drop

  void rotateClockwise();
  void rotateCClockwise();

  void shiftX(int shift);
  void shiftY(unsigned int shift);

  void drop();

  void setRandom();
  void setNotRandom(std::string source);

  bool isOver() const;
  int winner() const; //Returns -1 if isOver flag is not set
};

#endif
