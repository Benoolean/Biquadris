#include "../headers/square.h"
using namespace Biquadris;
using namespace std;

const string Square::emptySymbol = " ";

Square::Square(int x, int y, string symbol, int colour, bool active)
  : position({ x, y }), symbol(symbol), colour(colour), active(active) { }

bool Square::validPosition() {
  return position.isValidCoord();
}

bool Square::move(Direction direction, unsigned int shift) {
  // shift the coords of the square
  if (direction == Direction::LEFT) {
    this->position.x -= shift;
  }
  else if (direction == Direction::RIGHT) {
    this->position.x += shift;
  }
  else if (direction == Direction::DOWN) {
    this->position.y += shift;
  }

  return validPosition();
}

bool Square::move(Coordinate newPosition) {
  return validPosition();
}

void Square::deactivate() {
  symbol = emptySymbol;
  active = false;
}

void Square::mimic(const Square& s) {
  this->symbol = s.symbol;
  this->colour = s.colour;
  this->active = s.active;
}
