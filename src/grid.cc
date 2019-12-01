#include "grid.h"

Grid::Grid(int width, int height)
 : width(width), height(height) {}

Grid::~Grid() {
  delete active;
  delete dead;
}

void Grid::shiftX(int shift) {

}

void Grid::shiftY(int shift) {
  
}
