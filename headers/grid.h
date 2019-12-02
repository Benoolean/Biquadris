#ifndef GRID_H
#define GRID_H

#include <iostream>

#include "block.h"
#include "biquadris.h"

class Xwindow;

class Grid {
  Chunk* chunk;
  bool gridcomplete;
  const int width, height;

  Block* active;

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

  void checkRowCompleteness();
};

#endif
