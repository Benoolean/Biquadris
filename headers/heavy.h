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

  void draw(std::ostream* out, Xwindow* out) override; // Just calls component draw
  void shiftX(int shift) override; //Shifts down twice as well
};

#endif
