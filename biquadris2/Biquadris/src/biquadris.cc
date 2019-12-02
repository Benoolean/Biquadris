#include "../headers/biquadris.h"
#include "../headers/block.h"
#include "../headers/square.h"

namespace Biquadris {
  std::map<std::string, Block*> defaults;
  int seed = 0;

  void init(int seed) {
    Biquadris::seed = seed;

    defaults["I"] = new Block({
      new Square(0, 3, "I", 1, true),
      new Square(1, 3, "I", 1, true),
      new Square(2, 3, "I", 1, true),
      new Square(3, 3, "I", 1, true)
    });

    defaults["J"] = new Block({
      new Square(0, 2, "J", 2, true),
      new Square(0, 3, "J", 2, true),
      new Square(1, 3, "J", 2, true),
      new Square(2, 3, "J", 2, true)
    });

    defaults["L"] = new Block({
      new Square(0, 3, "L", 3, true),
      new Square(1, 3, "L", 3, true),
      new Square(2, 3, "L", 3, true),
      new Square(2, 2, "L", 3, true)
    });

    defaults["O"] = new Block({
      new Square(0, 3, "O", 4, true),
      new Square(0, 2, "O", 4, true),
      new Square(1, 3, "O", 4, true),
      new Square(1, 2, "O", 4, true)
    });

    defaults["S"] = new Block({
      new Square(0, 3, "S", 5, true),
      new Square(1, 3, "S", 5, true),
      new Square(1, 2, "S", 5, true),
      new Square(2, 2, "S", 5, true)
    });

    defaults["Z"] = new Block({
      new Square(0, 2, "Z", 6, true),
      new Square(1, 2, "Z", 6, true),
      new Square(1, 3, "Z", 6, true),
      new Square(2, 3, "Z", 6, true)
    });

    defaults["T"] = new Block({
      new Square(0, 2, "T", 7, true),
      new Square(1, 3, "T", 7, true),
      new Square(1, 2, "T", 7, true),
      new Square(2, 2, "T", 7, true)
    });
  }
}
