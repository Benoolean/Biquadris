#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "block.h"
#include "biquadris.h"
#include "coordinate.h"

struct Square;

class Chunk {
  std::vector<std::vector<Square*>> squares; // One dimensional array for improved efficiency
public:
  Chunk();
  ~Chunk();

  void addBlock(const Block& b); //Adds a block to the chunk
  void deactivateBlock(const Block& b); //Deactivates the given squares for the block
  void killBlock(const Block& b); //Kills the given squares on the grid

  void addSquare(const Square& s);
  void deactivateSquare(const Square& s);
  void deactivateCoordinate(Coordinate coord);

  int clearFullRows(); //Returns the number of full rows cleared and shifts upper dead content down

  const std::vector<std::vector<Square*>>& getSquares() const;
};

#endif
