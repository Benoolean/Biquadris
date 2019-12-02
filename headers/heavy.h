#ifndef HEAVY_H
#define HEAVY_H

#include "effect.h"

class Xwindow;

/*
 * Overrides shiftX to also shift down twice
 * Note: the horizontal shift occurs and thne
 */

class Heavy : public Effect {
public:
  Blind(Grid* component);
};

#endif
