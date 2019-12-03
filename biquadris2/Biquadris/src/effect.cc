#include "../headers/effect.h"
using namespace std;

Effect::Effect(Grid* component, bool limited, int maxLife)
  : Grid(), component(component), limited(limited), life(0), maxLife(life) { }

bool Effect::move(Biquadris::Direction direction) {
  bool valid = component->move(direction);
  if(!valid) ++life;
  return valid;
}

vector<vector<Square>> Effect::getPlayerChunk() {
  return component->getPlayerChunk();
}
