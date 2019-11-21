#ifndef BIQUADRIS_H
#define BIQUADRIS_H

class Block;

#include <map>

namespace Biquadris {
  std::map<char, Block> defaults;

  /*
   * Alternatively a file defining blocks could be created.
   * This, non-polymorphic, method makes the game much more
   * scalable.
   *
   * These defaults are simply copied whenever they are needed.
   */
  void init();
};

#endif
