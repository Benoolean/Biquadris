#include "level.h"

Level(const int level = 0,
  const int numPlayers = 2,
  const std::string* const source = nullptr,
  std::ostream* out = nullptr, Xwindow* window = nullptr)
    : level(level), out(out), window(window) {
  if(level > 4) {
    level = 4;
  }
}
