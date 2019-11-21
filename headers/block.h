#ifndef BLOCK_H
#define BLOCK_H

#include "square.h"

#include <vector>

class Block {
  std::vector<std::vector<Square>> squares;

  static bool touching(const Block&, const Block&);

public:
  Block();
  Block(std::vector<Square> &&squares);
  Block(const Block& other);
  Block(Block&& other);

  Block& operator=(const Block& rhs);
  Block& operator=(Block&& rhs); //Use squares.swap() (?)

  void addSquares(Block b);

  void addSquare(int x, int y); //Absolute coordinates
  void addSquare(const Square& s);

  void removeRow(int index); //Row index is relative to the squares vector not absolute coordinates

  void rotateClockwise();
  void rotateCClockwise();

  void shiftY(int squares); //Moves 'squares' on the y axis
  void shiftX(int squares); //Moves 'squares' on the x axis
};

#endif
