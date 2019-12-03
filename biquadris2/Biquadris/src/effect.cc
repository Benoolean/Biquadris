#include "../headers/effect.h"

Effect::Effect(Grid* component, bool limited, int life)
  : Grid(), component(component), limited(limited), life(life) { }
