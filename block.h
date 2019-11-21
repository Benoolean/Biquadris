#ifndef BLOCK_H
#define BLOCK_H

#include "square.h"

#include <vector>

class Block {
  std::vector<std::vector<Square>> squares;

public:
  Block();

  void addSquares(Block b);
  void removeRow(int index); //Row index is relative to the squares vector not absolute coordinates

  void rotateClockwise();
  void rotateCClockwise();

  void shiftY(int squares); //Moves 'squares' on the y axis
  void shiftX(int squares); //Moves 'squares' on the x axis
};

#endif
