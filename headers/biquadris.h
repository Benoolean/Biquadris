#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <map>

class Block;

namespace Biquadris {
  extern std::map<char, Block*> defaults;
  extern int seed;

  enum GridInfo { GRID_HEIGHT = 15, GRID_WIDTH = 11 };
  enum class Direction { LEFT, RIGHT, DOWN };

  enum class Effect {
    HEAVY, BLIND
  };

  /*
   * Alternatively a file defining blocks could be created.
   * This, non-polymorphic, method makes the game much more
   * scalable.
   *
   * These defaults are simply copied whenever they are needed.
   */
  void init(int seed = 0);
};

#endif
