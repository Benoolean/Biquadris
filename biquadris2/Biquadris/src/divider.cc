#include "../headers/divider.h"
using namespace Biquadris;

Divider::Divider(Grid* component) : Effect(component), turnsSinceRowsRemoved(0) { }

int Divider::checkRowCompleteness() {
  int removed = component->checkRowCompleteness();
  if(removed) {
    this->turnsSinceRowsRemoved = 0;
  }
  else {
    ++(this->turnsSinceRowsRemoved);
    if(this->turnsSinceRowsRemoved >= 5) {
      Block square = Block({ new Square(6, 0, "*", 9, SquareStatus::ACTIVE) });
      while(square->move(Direction::DOWN, 1, this->getChunk())) {}
    }
  }
}
