#ifndef EFFECT_H
#define EFFECT_H

#include "grid.h"

class Effect : public Grid {
protected:
  Grid* component;

  //Determines the life of an effect
  bool limited;
  int life;
public:
  Effect(Grid* component, bool limited = false, int life = 0);
};

#endif
