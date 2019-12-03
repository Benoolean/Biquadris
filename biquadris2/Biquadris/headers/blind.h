#ifndef BLIND_H
#define BLIND_H

#include "effect.h"
/*
 * Overrides draw to hide columns 3-9 and rows 3-12
 */

class Blind : public Effect {
public:
  Blind(Grid* component);
};

#endif
