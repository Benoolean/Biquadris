#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "block.h"

class Square;

class Chunk {
  std::vector<Square*> squares; // One dimensional array for improved efficiency
public:
  Chunk();
  ~Chunk();

  void addBlock(const Block& b); //Adds a block to the chunk
  void deactivateBlock(const Block& b); //Deactivates the given squares for the block

  void addSquare(const Square& s);
  void deactivateSquare(const Square& s);

  const std::vector<Square*>& getSquares() const;
};

#endif
