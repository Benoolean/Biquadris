#include "../headers/heavy.h"
using namespace Biquadris;

Heavy::Heavy(Grid* component, int gravity) : Effect(component), gravity (gravity) { }

bool Heavy::move(Direction direction) {
  bool moved = component->move(direction);

  //Shift down twice if horizontal movement
  if(direction != Direction::DOWN) {
    for(int i = 0; i < this->gravity && moved; i++) {
      moved = component->move(Direction::DOWN);
    }
  }

  if(!moved) ++life;

  return moved;
}
