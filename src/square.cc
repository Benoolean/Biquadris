#include "square.h"
using namespace Biquadris;

Square::Square(int x, int y, char symbol, bool active)
  : x(x), y(y), symbol(symbol), active(active) { }

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
