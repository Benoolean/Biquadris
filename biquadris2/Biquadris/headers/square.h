#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "coordinate.h"
#include "biquadris.h"

enum class SquareStatus { ACTIVE, INACTIVE, DEAD };

struct Square {
  static const std::string emptySymbol;

  Square(int x, int y, std::string symbol = emptySymbol, int colour = 0, SquareStatus status = SquareStatus::INACTIVE);

  Coordinate position;
  std::string symbol; //String to represent the block on output
  int colour;
  SquareStatus status;

  bool validPosition();

  bool move(Biquadris::Direction direction, unsigned int shift = 1);
  bool move(Coordinate newPosition);

  void kill();
  void deactivate();
  void mimic(const Square& s); //Copies the graphical info for this square
};

#endif
