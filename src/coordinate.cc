#include "coordinate.h"
#include "biquadris.h"

bool Coordinate::isValidCoord()	{
  return (x >= 0 && x <= Biquadris::GridInfo::GRID_WIDTH
          && y >= 0 && y <= Biquadris::GridInfo::GRID_HEIGHT);
}

Coordinate Coordinate::getNeighbouringCoordinate(Direction direction) {
  if (direction.getDirection() == DirectionValue::LEFT) {
    return Coordinate{ x - 1, y };
  }
  else if (direction.getDirection() == DirectionValue::RIGHT) {
    return Coordinate{ x + 1, y };
  }
  else {
    return Coordinate{ x, y + 1 };
  }
}
