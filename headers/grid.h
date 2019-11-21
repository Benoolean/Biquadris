#ifndef GRID_H
#define GRID_H

#include <iostream>

class Grid {
  Block* active;
  Block* dead;

public:
  virtual ~Grid();

  virtual void draw(std::ostream* out, Xwindow* window) = 0;

  bool isActive(); // Returns true if there is an active block, false otherwise
  void setActive(Block* newActive);

  /*
   * Each movement function checks if the move is legal or if the block will contact
   * the deadspace. In the former case nothing happens, in the latter case active is
   * added to dead and then deleted.
   */
  virtual void shiftX(int shift);
  virtual void shiftY(int shift);
};

#endif
