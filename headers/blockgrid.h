#ifndef BLOCKGRID_H
#define BLOCKGRID_H

#include "grid.h"

class BlockGrid : public Grid {
public:
  void draw(std::ostream* out, Xwindow* window) override;
};

#endif
