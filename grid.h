#ifndef GRID_H
#define GRID_H

#include <iostream>

class Grid {
  Block* active;
  Block* dead;

public:
  virtual void draw(std::ostream* out, Xwindow* window) = 0;

  virtual void shiftX() = 0;
  virtual void shiftY() = 0;
};

#endif
