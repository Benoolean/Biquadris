#include "../headers/heavy.h"
using namespace Biquadris;

Heavy::Heavy(Grid* component) : Effect(component) { }

bool Heavy::move(Direction direction) {
  bool moved = component->move(direction);

  //Shift down twice if horizontal movement
  if(direction != Direction::DOWN && moved) {
    moved = component->move(Direction::DOWN);
    if(moved) moved = component->move(Direction::DOWN);
  }

  return moved;
}
