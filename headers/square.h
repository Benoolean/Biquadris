#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "coordinate.h"
#include "biquadris.h"

struct Square {
  const static emptySymbol = " ";

  Square(int x, int y, string symbol = emptySymbol, bool active = false);

  Coordinate position;
  std::string symbol; //String to represent the block on  output
  bool active;

  bool validPosition();

  bool move(Biquadris::Direction direction, unsigned int shift = 1);
  bool move(Coordinate newPosition);

  void deactivate();
};

#endif
