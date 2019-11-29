#include "block.h"
using namespace std;

Block::Block() {

}

Block::Block(std::vector<std::vector<Square>> &&squares) {
  this->squares.swap(squares);
}

Block::Block(const Block &other) noexcept {
  squares = other.getSquares();
}

Block::Block(Block &&other) noexcept {
  squares = other.getSquares();
}

Block& Block::operator=(const Block& rhs) noexcept {
  squares = rhs.getSquares();
  return *this;
}

Block& Block::operator=(Block&& rhs) noexcept {
  squares = rhs.getSquares();
  return *this;
}

int Block::getWidth() const {
  return squares.size();
}

int Block::getHeight() const {
  //Can reliably choose a random index, because adding squares
  //ensures that all rows have the same number of columns
  return squares[0].size();
}

//Helper function that creates a row of Squares
vector<Square> createRow(int x, int y, int height) {
  vector<Square> r;
  for(int i = 0; i < height; i++) {
    r.emplace_back(Square(x, y + i));
  }
  return r;
}

void Block::addSquares(const Block& b) {
  if(squares.size()) {
    Square thisTL = squares[0][0];
    const vector<vector<Square>>& s = b.getSquares();
    Square bTL = s[0][0];

    int xDif = thisTL.x - bTL.x;
    int yDif = thisTL.y - bTL.y;

    /*
     * Padding refers to the extra squares to be added to a side
     * For example right padding of 2, will add two new columns
     */
    int lPadding = ((xDif > 0) ? xDif : 0);
    int tPadding = ((yDif > 0) ? yDif : 0);

    int rPadding = (bTL.x + b.getWidth()) - (thisTL.x + getWidth());
    rPadding = ((rPadding > 0) ? rPadding : 0);
    int bPadding = (bTL.y + b.getHeight()) - (thisTL.y + getHeight());
    bPadding = ((bPadding > 0) ? bPadding : 0);

    for(int i = 1; i <= lPadding; i++) { //Left padding
      squares.insert(squares.begin(), createRow(squares[0][0].x - i, squares[0][0].y, getHeight()));
    }
    for(int i = 1; i <= rPadding; i++) { //Right padding
      squares.emplace_back(createRow(squares[0][0].x + getWidth() - 1 + i, squares[0][0].y, getHeight()));
    }
    for(int i = 1; i <= tPadding; i++) {
      for(int j = 0; j < getWidth(); j++) {
        squares[j].insert(squares[j].begin(), Square(squares[0][0].x + j, squares[0][0].y - i));
      }
    }
    for(int i = 1; i <= bPadding; i++) {
      for(int j = 0; j < getWidth(); j++) {
        squares[j].emplace_back(Square(squares[0][0].x + j, squares[0][0].y + getHeight() - 1 + i));
      }
    }

    thisTL = squares[0][0];
    for(int i = 0; i < b.getWidth(); i++) {
      for(int j = 0; j < b.getHeight(); j++) {
        squares[thisTL.x - s[i][j].x][thisTL.y - s[i][j].y].active = s[i][j].active;
      }
    }
  }
  else {
    squares = b.getSquares();
  }
}

void Block::addSquare(int x, int y) {

}

void Block::addSquare(const Square& s) {

}

void Block::removeRow(int index) {

}

void Block::rotateClockwise() {

}

void Block::rotateCClockwise() {

}

void Block::shiftY(int squares) {

}

void Block::shiftX(int squares) {

}

const std::vector<std::vector<Square>>& Block::getSquares() const {
  return squares;
}

bool Block::touching(const Block& other) const {
  return false;
}
