#include "../headers/effect.h"
using namespace std;

Effect::Effect(Grid* component, bool limited, int maxLife)
  : Grid(), component(component), limited(limited), life(0), maxLife(maxLife) { }

Chunk* Effect::getChunk() {
  return component->getChunk();
}

void Effect::setComponent(Grid* component) {
  this->component = component;
}

bool Effect::move(Biquadris::Direction direction) {
  bool valid = component->move(direction);
  if(!valid) ++life;
  return valid;
}

int Effect::checkRowCompleteness() {
  return component->checkRowCompleteness();
}

vector<vector<Square>> Effect::getPlayerChunk() {
  return component->getPlayerChunk();
}
