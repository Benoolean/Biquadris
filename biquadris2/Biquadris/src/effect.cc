#include "../headers/effect.h"
using namespace std;

Effect::Effect(Grid* component, bool limited, int life)
  : Grid(), component(component), limited(limited), life(life) { }

bool Effect::move(Biquadris::Direction direction) {
  bool valid = component->move(direction);
  if(!valid) --this->life;

  return valid;
}

vector<vector<Square>> Effect::getPlayerChunk() {
  return component->getPlayerChunk();
}
