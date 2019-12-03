#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

#include "biquadris.h"

struct Square;
class Chunk;

class Block
{
	static int masterUID;

	std::vector<Square*> squares; //Column by row

	int creationLevel;

	int uid;
	void generateUID();

public:
	Block();
	Block(std::vector<Square*>&& squares, int creationLevel = -1);
	Block(const Block& other, int creationLevel = -1);

	~Block();

	void setCreationLevel(int creationLevel);
	int getCreationLevel() const;
	/*
	 * Any movement functions that returns a boolean
	 * indicates whether they contact the provided Chunk
	 * (returns false in case of contact).
	 * Furthermore, any movement requested that is invalid
	 * is not performed.
	 */

	int getUID() const;

	void rotateClockwise(Chunk* chunk = nullptr);
	void rotateCClockwise(Chunk* chunk = nullptr);

	bool move(Biquadris::Direction direction, int shift = 1, Chunk * chunk = nullptr);

	const std::vector<Square*>& getSquares() const;
};

#endif
