#include <string>
#include <vector>

#include "blockgrid.h"

class Player {
  BlockGrid* grid;

  std::string source; //This allows a new stream to be opened once the end of either hase been reached
  std::vector<std::string> sequence; // Pushed from specified fstream, and stack popped every drop

  int level;
  int points;

public:
  Player(std::string source, int level = 0);
  ~Player();

  friend class Level;
};
