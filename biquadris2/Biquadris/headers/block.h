#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

#include "biquadris.h"

class Square;
class Chunk;

class Block {
  std::vector<Square*> squares; //Column by row

public:
  Block();
  Block(std::vector<Square*> &&squares);
  Block(const Block& other);

  ~Block();


  /*
   * Any movement functions that returns a boolean
   * indicates whether they contact the provided Chunk
   * (returns false in case of contact).
   * Furthermore, any movement requested that is invalid
   * is not performed.
   */

  void rotateClockwise(Chunk* chunk = nullptr);
  void rotateCClockwise(Chunk* chunk = nullptr);

  bool move(Biquadris::Direction direction, int shift = 1, Chunk* chunk = nullptr);

  const std::vector<Square*>& getSquares() const;
};

#endif
