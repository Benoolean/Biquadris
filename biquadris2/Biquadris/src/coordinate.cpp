#include "coordinate.h"
using namespace Biquadris;

bool Coordinate::isValidCoord()	{
  return (x >= 0 && x <= GridInfo::GRID_WIDTH
          && y >= 0 && y <= GridInfo::GRID_HEIGHT);
}

Coordinate Coordinate::getNeighbouringCoordinate(Direction direction) {
  if (direction == Direction::LEFT) {
    return Coordinate{ x - 1, y };
  }
  else if (direction == Direction::RIGHT) {
    return Coordinate{ x + 1, y };
  }
  else { //Otherwise Direction::DOWN
    return Coordinate{ x, y + 1 };
  }
}
