#ifndef SQUARE_H
#define SQUARE_H

struct Square {
  Square(int x, int y, bool active = true);

  int coords[2]; //(0: x, 1: y)
  bool active;
};

#endif
