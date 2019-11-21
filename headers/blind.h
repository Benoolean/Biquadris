#ifndef BLIND_H
#define BLIND_H

#include "effect.h"

class Xwindow;

/*
 * Overrides draw to hide columns 3-9 and rows 3-12
 */

class Blind : public Effect {
public:
  Blind(Grid* component);

  void draw(std::ostream* out, Xwindow* out) override; // Standard draw but overlays the blinded position
};

#endif
