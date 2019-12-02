#include <vector>

#include "block.h"

class Square;

class Chunk {
  std::vector<Square*> squares; // One dimensional array for improved efficiency
public:
  Chunk();
  ~Chunk();

  void addBlock(const Block& b); //Adds a block to the chunk
  void deactivateBlock(const Block& b); //Deactivates the given squares for the block
};
