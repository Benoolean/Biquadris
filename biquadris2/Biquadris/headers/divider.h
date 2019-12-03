#ifndef DIVIDER_H
#define DIVIDER_H

#include "effect.h"

class Divider : public Effect {
  int turnsSinceRowsRemoved;
public:
  Divider(Grid* component);
  virtual int checkRowCompleteness() override;
};

#endif
