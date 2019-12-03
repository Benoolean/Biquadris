#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <vector>
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

  int uid;

  bool validPosition();

  bool move(Biquadris::Direction direction, unsigned int shift = 1);

  void kill();
  void deactivate();
  void mimic(const Square& s); //Copies the graphical info for this square
};


Coordinate getCounterClockWiseRotationCoord(Square* square);
Coordinate getPivitolCoordinate(std::vector<Coordinate> squares);

#endif
