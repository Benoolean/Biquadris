#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

#include "square.h"

class Block {
  std::vector<std::vector<Square>> squares; //Column by row

public:
  Block();
  Block(std::vector<std::vector<Square>> &&squares);
  Block(const Block& other) noexcept;
  Block(Block&& other) noexcept;

  Block& operator=(const Block& rhs) noexcept;
  Block& operator=(Block&& rhs) noexcept; //Use squares.swap() (?)

  int getWidth() const;
  int getHeight() const;

  void addSquares(const Block& b);

  void addSquare(int x, int y); //Absolute coordinates
  void addSquare(const Square& s);

  void removeRow(int index); //Row index is relative to absolute coordinates

  void rotateClockwise();
  void rotateCClockwise();

  void shiftY(int shift); //Moves 'squares' on the y axis
  void shiftX(int shift); //Moves 'squares' on the x axis

  bool touching(const Block& other) const; //Check if the given block is touching another

  const std::vector<std::vector<Square>>& getSquares() const;

  friend std::ostream& operator<<(std::ostream& out, const Block& b);
};

#endif
