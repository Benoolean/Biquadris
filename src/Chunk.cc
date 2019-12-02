#include "Chunk.h"
#include "square.h"

#include "biquadris.h"

using namespace std;

Chunk::Chunk() {
  for(int i = 0; i < Biquadris::GridInfo::GRID_WIDTH * Biquadris::GridInfo::GRID_HEIGHT; i++) {
    
  }
}

Chunk::~Chunk() {
  for(auto square : squares) {
    delete square;
  }
}
