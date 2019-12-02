#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {
	int x;
	int y;

	bool isValidCoord();
	Coordinate getNeighbouringCoordinate(Direction direction);
};

#endif
