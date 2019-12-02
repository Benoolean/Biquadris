#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <map>

#include "block.h"

namespace Biquadris {
  extern std::map<char, Block*> defaults;
  extern int seed;

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
