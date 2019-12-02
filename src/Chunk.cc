#include "Chunk.h"
#include "square.h"

#include "biquadris.h"

using namespace std;

Chunk::Chunk() {
  for(int i = 0; i < Biquadris::GridInfo::GRID_WIDTH * Biquadris::GridInfo::GRID_HEIGHT; i++) {
    squares.push_back(new Square());
  }
}

Chunk::~Chunk() {
  for(auto square : squares) {
    delete square;
  }
}

void Block::addBlock(const Block& b) {
  const vector<Square*>& bSquares = b.getSquares();
  for(int i = 0; i < bSquares.size(); i++) {
    squares[bSquares[i].position.x + (bSquares[i].position.y * Biquadris::GridInfo::GRID_WIDTH)].mimic(bSquares[i]);
  }
}

void Block::deactivateBlock(const Block& b) {
  const vector<Square*>& bSquares = b.getSquares();
  for(int i = 0; i < bSquares.size(); i++) {
    squares[bSquares[i].position.x + (bSquares[i].position.y * Biquadris::GridInfo::GRID_WIDTH)].deactivate();
  }
}

void Block::addSquare(const Square& s) {
  squares[s.position.x + (s.position.y * Biquadris::GridInfo::GRID_WIDTH)].mimic(s);
}

void Block::deactivateBlock(const Block& s) {
  squares[s.position.x + (s.position.y * Biquadris::GridInfo::GRID_WIDTH)].deactivate();
}

const std::vector<Square>& Chunk::getSquares() const {
  return squares;
}
