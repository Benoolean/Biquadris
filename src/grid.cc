#include "grid.h"
using namespace std;
using namespace Biquadris;

Grid::Grid()
  : width(GridInfo::GRID_WIDTH),
    height(GridInfo::GRID_HEIGHT),
    active(nullptr) { }

Grid::~Grid() {
  delete active;
  delete dead;
}

void Grid::move(Direction direction) {

}

void Grid::checkRowCompleteness() {

}
