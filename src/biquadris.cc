#include "biquadris.h"
#include "block.h"

namespace Biquadris {
  std::map<char, Block*> defaults;

  void init() {
    defaults['I'] = new Block({ Square(0, 14), Square(1, 14), Square(2, 14), Square(3, 14) });

    defaults['J'] = new Block();

    defaults['L'] = new Block();

    defaults['O'] = new Block();

    defaults['S'] = new Block();

    defaults['Z'] = new Block();

    defaults['T'] = new Block();
  }
}
