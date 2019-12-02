#ifndef COORDINATE_H
#define COORDINATE_H

#include "biquadris.h"

struct Coordinate {
	int x;
	int y;

	bool isValidCoord();
	Coordinate getNeighbouringCoordinate(Biquadris::Direction direction);
};

#endif
