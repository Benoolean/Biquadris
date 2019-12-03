#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <map>
#include <string>

class Block;

namespace Biquadris {
  extern std::map<std::string, Block*> defaults;
  extern int seed;

  enum GridInfo { GRID_HEIGHT = 18, GRID_WIDTH = 11 }; //Height = 15 + 3 safety rows
  enum class Direction { LEFT, RIGHT, DOWN };

  enum class EffectType {
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
