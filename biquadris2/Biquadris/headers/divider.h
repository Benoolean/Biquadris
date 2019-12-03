#ifndef DIVIDER_H
#define DIVIDER_H

#include "effect.h"

class Divider : public Effect {
public:
  Divider(Grid* component);
  virtual bool move(Biquadris::Direction direction) override;
};

#endif
