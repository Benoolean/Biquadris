#ifndef EFFECT_H
#define EFFECT_H

#include "grid.h"

class Effect : public Grid {
protected:
  Grid* component;
public:
  Effect(Grid* component);
};

#endif
