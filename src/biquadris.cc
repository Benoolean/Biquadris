#include "biquadris.h"
#include "block.h"

namespace Biquadris {
  std::map<char, Block*> defaults;
  int seed = 0;

  void init(int seed) {
    Biquadris::seed = seed;

    defaults['I'] = new Block({ { Square(0, 3, 'I', true) }, { Square(1, 3, 'I', true) }, { Square(2, 3, 'I', true) }, { Square(3, 3, 'I', true) } });

    defaults['J'] = new Block();

    defaults['L'] = new Block();

    defaults['O'] = new Block();

    defaults['S'] = new Block();

    defaults['Z'] = new Block();

    defaults['T'] = new Block();
  }
}
