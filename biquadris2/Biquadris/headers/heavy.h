#ifndef HEAVY_H
#define HEAVY_H

#include "effect.h"

/*
 * Overrides shiftX to also shift down twice
 * Note: the horizontal shift occurs and then
 * the vertical shift
 */

class Heavy : public Effect {
  int gravity;
public:
  Heavy(Grid* component, int gravity=2);
  virtual bool move(Biquadris::Direction direction) override;
};

#endif
