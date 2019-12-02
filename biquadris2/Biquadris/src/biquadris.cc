#include "../headers/biquadris.h"
#include "../headers/block.h"
#include "../headers/square.h"

namespace Biquadris {
  std::map<char, Block*> defaults;
  int seed = 0;

  void init(int seed) {
    Biquadris::seed = seed;

    defaults['I'] = new Block({
      new Square(0, 3, "I", 1, true),
      new Square(1, 3, "I", 1, true),
      new Square(2, 3, "I", 1, true),
      new Square(3, 3, "I", 1, true)
    });

    defaults['J'] = new Block();

    defaults['L'] = new Block();

    defaults['O'] = new Block();

    defaults['S'] = new Block();

    defaults['Z'] = new Block();

    defaults['T'] = new Block();
  }
}
