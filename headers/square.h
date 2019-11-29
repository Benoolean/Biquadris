#ifndef SQUARE_H
#define SQUARE_H

struct Square {
  Square(int x, int y, char symbol = ' ', bool active = false);

  int x, y; //(0: x, 1: y)
  char symbol; //Character to represent the block on output
  bool active;
};

#endif
