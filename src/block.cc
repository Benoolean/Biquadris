#include "block.h"
#include "coordinate.h"
using namespace std;

Block::Block() { }

Block::Block(std::vector<Square*> &&squares) {
  this->squares.swap(squares);
}

Block::~Block() {
  for(auto square : squares) {
    delete square;
  }
}

void Block::rotateClockwise() {

}

void Block::rotateCClockwise() {

}

bool Block::move(Biquadris::Direction direction, unsigned int shift, Chunk* chunk) {
  int shiftX = 0, shiftY = 0;

  if (direction == Direction::LEFT) {
    shiftX = -shift;
  }
  else if (direction == Direction::RIGHT) {
    shiftX = shift;
  }
  else if (direction == Direction::DOWN) {
    shiftY = shift;
  }

  bool contacts = false;

  for(auto s : this->squares) {
    Coordinate newPosition { s->position.x + shiftX, s->position.y + shiftY };
    if(newPosition.isValidCoord()) {
      if(chunk) {
        if(chunk->getSquares()[(s->position.x + shiftX) + ((s->position.y + shiftY) * Biquadris::GridInfo::GRID_WIDTH)].active) {
          contacts = true;
          break;
        }
      }
    }
    else return true;
  }

  if(contacts && direction == Direction::DOWN) { //The blocks should die
      return false;
  }
  else { //If there is no contact, then move the Block
    for(auto s : this->squares) {
      s->position.x += shiftX;
      s->position.y += shiftY;
    }

    if(chunk) {
      chunk->deactivateBlock(*this);
      chunk->addBlock(*this);
    }
  }

  return true;
}

const std::vector<Square>& Block::getSquares() const {
  return squares;
}
