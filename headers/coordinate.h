struct Coordinate {
	int x;
	int y;

	bool isValidCoord();
	Coordinate getNeighbouringCoordinate(Direction direction);
};
