#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>

#include "block.h"
#include "biquadris.h"

class Grid {
protected:
  Chunk* chunk;
  bool gridcomplete;
  Block* active;

  std::vector<Block*> deadBlocks;

  virtual Chunk* getChunk();

public:
  Grid();
  virtual ~Grid();

  bool isActive(); // Returns true if there is an active block, false otherwise
  bool setActive(Block* newActive); // Returns false if illegal placement (contacts dead)

  /*
   * Each movement function checks if the move is legal or if the block will contact
   * the deadspace. In the former case nothing happens, in the latter case active is
   * added to dead and then deleted.
   */
  virtual bool move(Biquadris::Direction direction);
  virtual void rotateCClockwise();
  virtual void rotateClockwise();

  virtual int checkRowCompleteness();
  int deadBlocksRemoved(); //Returns the points gained from removal

  bool isComplete();

  virtual std::vector<std::vector<Square>> getPlayerChunk();

  friend class Effect;
};

#endif
