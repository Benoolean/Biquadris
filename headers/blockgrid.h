#ifndef BLOCKGRID_H
#define BLOCKGRID_H

#include "grid"

class BlockGrid : public Grid {
public:
  BlockGrid();
  void draw(std::ostream* out, Xwindow* window) override;
};

#endif
