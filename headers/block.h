#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "square.h"

class Block {
  std::vector<std::vector<Square>> squares;

public:
  Block();
  Block(std::vector<Square> &&squares);
  Block(const Block& other);
  Block(Block&& other);

  Block& operator=(const Block& rhs);
  Block& operator=(Block&& rhs); //Use squares.swap() (?)

  void addSquares(const Block& b);

  void addSquare(int x, int y); //Absolute coordinates
  void addSquare(const Square& s);

  void removeRow(int index); //Row index is relative to the squares vector not absolute coordinates

  void rotateClockwise();
  void rotateCClockwise();

  void shiftY(int squares); //Moves 'squares' on the y axis
  void shiftX(int squares); //Moves 'squares' on the x axis

  const std::vector<std::vector<Square>>& getSquares();
  friend bool touching(const Block& b1, const Block& b2); //Check if the given block is touching another
};

#endif
