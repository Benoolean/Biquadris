#include "biquadris.h"
#include "block.h"

namespace Biquadris {
  std::map<char, Block*> defaults;
  int seed = 0;

  void init(int seed) {
    Biquadris::seed = seed;

    defaults['I'] = new Block({ { Square(0, 3) }, { Square(1, 3) }, { Square(2, 3) }, { Square(3, 3) } });

    defaults['J'] = new Block();

    defaults['L'] = new Block();

    defaults['O'] = new Block();

    defaults['S'] = new Block();

    defaults['Z'] = new Block();

    defaults['T'] = new Block();
  }
}
