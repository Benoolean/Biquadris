#include "../headers/coordinate.h"
#include "../headers/block.h"
#include "../headers/square.h"
#include "../headers/Chunk.h"
using namespace std;
using namespace Biquadris;

int Block::masterUID = 0;

Block::Block() : creationLevel(-1) { }

Block::Block(std::vector<Square*>&& squares, int creationLevel)
	: creationLevel(creationLevel)
{
	this->squares.swap(squares);
	generateUID();
}

Block::Block(const Block& other, int creationLevel)
	: creationLevel(creationLevel)
{
	const vector<Square*>& otherSquares = other.getSquares();
	for (int i = 0; i < otherSquares.size(); i++)
	{
		this->squares.push_back(new Square(*otherSquares[i]));
	}

	generateUID();
}

Block::~Block()
{
	for (auto square : squares)
	{
		delete square;
	}
}

void Block::generateUID() {
	for(auto square : this->squares) {
		square->uid = masterUID;
	}
	this->uid = masterUID;
	++masterUID;
}

void Block::setCreationLevel(int creationLevel) {
	this->creationLevel = creationLevel;
}

int Block::getCreationLevel() const {
	return this->creationLevel;
}

int Block::getUID() const {
	return this->uid;
}

void Block::rotateClockwise(Chunk* chunk)
{
	this->rotateCClockwise(chunk);
	this->rotateCClockwise(chunk);
	this->rotateCClockwise(chunk);
}

void Block::rotateCClockwise(Chunk* chunk)
{
	vector<Square*> squares = this->getSquares();

	// algorithm
	// multiply by matrix[ (0 -1) (1 0)] and offset it with pivital

	vector<Coordinate> squareCoordinates;
	for (auto square : squares)
	{
		squareCoordinates.push_back(Coordinate{ square->position.x, square->position.y });
	}

	vector<Coordinate> squareCoordinatesAfterOriginRotation;
	for (auto square : squares)
	{
		Coordinate rotationFromOrigin = getCounterClockWiseRotationCoord(square);
		squareCoordinatesAfterOriginRotation.push_back(rotationFromOrigin);
	}

	// get pivitol coords for both before and after transformation
	Coordinate squarePivitol = getPivitolCoordinate(squareCoordinates);
	Coordinate squarePivitolAfterOriginRotation = getPivitolCoordinate(squareCoordinatesAfterOriginRotation);

	// find the shift value
	int shiftx = squarePivitolAfterOriginRotation.x - squarePivitol.x;
	int shifty = squarePivitolAfterOriginRotation.y - squarePivitol.y;

	// for each coord in the transformed coords, apply shift
	for (auto & coord : squareCoordinatesAfterOriginRotation)
	{
		coord.x = coord.x - shiftx;
		coord.y = coord.y - shifty;

		//coord = Coordinate{ coord.x , coord.y };
	}

	// check if the rotation is valid -> hence all squares at chunk with squareCoordinatesAfterOriginRotation
	// must be inactive and valid
	for (auto coord : squareCoordinatesAfterOriginRotation)
	{
		if (!coord.isValidCoord())
		{
			return;
		}
	}

	// deactive the current active block
	for (auto coord : squareCoordinates)
	{
		chunk->deactivateCoordinate(coord);
	}

	// for the current active block, update the square coordinates
	// and the chunk squares
	for (int squarecount = 0; squarecount < squares.size(); squarecount++)
	{
		Coordinate newCoord = squareCoordinatesAfterOriginRotation.at(squarecount);
		squares.at(squarecount)->position.x = newCoord.x;
		squares.at(squarecount)->position.y = newCoord.y;

		chunk->addSquare(*squares.at(squarecount));
	}
}

bool Block::move(Biquadris::Direction direction, int shift, Chunk* chunk)
{
	int shiftX = 0, shiftY = 0;

	if (direction == Direction::LEFT)
	{
		shiftX = -shift;
	}
	else if (direction == Direction::RIGHT)
	{
		shiftX = shift;
	}
	else if (direction == Direction::DOWN)
	{
		shiftY = shift;
	}

	bool contacts = false;

	for (auto square : this->squares)
	{
		Coordinate newPosition{ square->position.x + shiftX, square->position.y + shiftY };
		if (newPosition.isValidCoord())
		{
			if (chunk)
			{
				int posx = square->position.x + shiftX;
				int posy = square->position.y + shiftY;

				if (chunk->getSquares().at(posy).at(posx)->status == SquareStatus::DEAD)
				{
					contacts = true;
					break;
				}
			}
		}
		else
		{
			if (newPosition.y >= GridInfo::GRID_HEIGHT)
			{
				contacts = true;
				break;
			}
			else return true;
		}
	}

	if (contacts && direction == Direction::DOWN)
	{ //The blocks should die
		chunk->killBlock(*this);
		return false;
	}
	else if(!contacts)
	{
		//If there is no contact, then move the Block
		if(chunk) {
			chunk->deactivateBlock(*this);
		}

		for (auto s : this->squares)
		{
			s->position.x += shiftX;
			s->position.y += shiftY;
		}

		if (chunk)
		{
			chunk->addBlock(*this);
		}
	}

	return true;
}

const std::vector<Square*>& Block::getSquares() const
{
	return squares;
}

Square* Block::getSquareFromCoordinate(Coordinate coord)
{
	vector<Square*> squares = this->getSquares();

	for (auto square : squares)
	{
		if (square->position.x == coord.x && square->position.y == coord.y)
		{
			return square;
		}
	}

	return nullptr;
}

std::vector<Coordinate> Block::getCoordinates()
{
	vector<Square*> squares = this->getSquares();
	vector<Coordinate> coordinates;

	for (auto square : squares)
	{
		coordinates.push_back(Coordinate{ square->position.x, square->position.y });
	}

	return coordinates;
}

std::vector<Coordinate> Block::getNormalizedCoordinates()
{
	vector<Coordinate> coords = this->getCoordinates();

	Coordinate topleftCorner = this->getTopLeftCornerWwithPadding();

	int shiftx = topleftCorner.x;
	int shifty = topleftCorner.y;

	for (auto& coord : coords)
	{
		coord.x = coord.x - shiftx;
		coord.y = coord.y - shifty;
	}

	return coords;
}

Coordinate Block::getTopLeftCornerWwithPadding()
{
	try
	{
		vector<Square*> squares = this->getSquares();

		int posx = squares.at(0)->position.x;
		int posy = squares.at(0)->position.y;

		for (auto square : squares)
		{
			posx = (square->position.x <= posx) ? square->position.x : posx;
			posy = (square->position.y <= posy) ? square->position.y : posy;
		}

		return Coordinate{ posx, posy };
	}
	catch (exception const& expect)
	{
		cout << "Unable to obtain block top left corner with padding!" << endl;
		cout << "Error: " << expect.what() << endl;
	}
}

Coordinate Block::getBottomRightCornerWwithPadding()
{
	try
	{
		vector<Square*> squares = this->getSquares();

		int posx = squares.at(0)->position.x;
		int posy = squares.at(0)->position.y;

		for (auto square : squares)
		{
			posx = (square->position.x >= posx) ? square->position.x : posx;
			posy = (square->position.y >= posy) ? square->position.y : posy;
		}

		return Coordinate{ posx, posy };
	}
	catch (exception const& expect)
	{
		cout << "Unable to obtain block bottom right corner with padding!" << endl;
		cout << "Error: " << expect.what() << endl;
	}
}

//void Block::draw()
//{
//	Coordinate topleftCorner = this->getTopLeftCornerWwithPadding();
//	Coordinate bottomRightCorner = this->getBottomRightCornerWwithPadding();
//
//	vector<Coordinate> coordsNormalized = this->getNormalizedCoordinates();
//
//	int width = (int) (bottomRightCorner.x - topleftCorner.x) + 1;
//	int height = (int) (bottomRightCorner.y - topleftCorner.y) + 1;
//
//	int shiftx = topleftCorner.x;
//	int shifty = topleftCorner.y;
//
//	vector<vector<string>> nextBlockGrid;
//
//	// init the grid
//	for (int rowcount = 0; rowcount < height; rowcount++)
//	{
//		vector<string> row = vector<string>(width);
//		nextBlockGrid.push_back(row);
//
//		for (int colcount = 0; colcount < width; colcount++)
//		{
//			int squareposx = colcount + shiftx;
//			int squareposy = rowcount + shifty;
//			Square* square = this->getSquareFromCoordinate(Coordinate{ squareposx, squareposy });
//
//			string symbol = (square != nullptr) ? square->symbol : " ";
//			nextBlockGrid.at(rowcount).push_back(symbol);
//		}
//	}
//
//
//	// print
//	// fill grid
//	for (auto row : nextBlockGrid)
//	{
//		for (auto col : row)
//		{
//			cout << col;
//		}
//		cout << endl;
//	}
//}
