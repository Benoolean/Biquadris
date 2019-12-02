#include "../headers/Chunk.h"
#include "../headers/square.h"

#include "../headers/biquadris.h"

#include <iostream>

#include <iostream>

using namespace std;

Chunk::Chunk() {
  for(int i = 0; i < Biquadris::GridInfo::GRID_WIDTH * Biquadris::GridInfo::GRID_HEIGHT; i++) {
    squares.push_back(new Square(i % Biquadris::GridInfo::GRID_WIDTH, i / Biquadris::GridInfo::GRID_WIDTH));
  }
}

Chunk::~Chunk() {
  for(auto square : squares) {
    delete square;
  }
}

void Chunk::addBlock(const Block& b) {
  const vector<Square*>& bSquares = b.getSquares();
  for(int i = 0; i < bSquares.size(); i++) {
    squares[bSquares[i]->position.x + (bSquares[i]->position.y * Biquadris::GridInfo::GRID_WIDTH)]->mimic(*bSquares[i]);
  }
}

void Chunk::deactivateBlock(const Block& b) {
  const vector<Square*>& bSquares = b.getSquares();
  for(int i = 0; i < bSquares.size(); i++) {
    squares[bSquares[i]->position.x + (bSquares[i]->position.y * Biquadris::GridInfo::GRID_WIDTH)]->deactivate();
  }
}

void Chunk::addSquare(const Square& s) {
  squares[s.position.x + (s.position.y * Biquadris::GridInfo::GRID_WIDTH)]->mimic(s);
}

void Chunk::deactivateSquare(const Square& s) {
  squares[s.position.x + (s.position.y * Biquadris::GridInfo::GRID_WIDTH)]->deactivate();
}

const std::vector<Square*>& Chunk::getSquares() const {
  return squares;
}
