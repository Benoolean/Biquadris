#ifndef EFFECT_H
#define EFFECT_H

#include "../headers/biquadris.h"
#include "../headers/grid.h"
#include "../headers/square.h"

#include <vector>

class Effect : public Grid {
protected:
  Grid* component;

  //Determines the life of an effect
  bool limited;
  int maxLife;
  int life;

  virtual Chunk* getChunk() override;

public:
  Effect(Grid* component, bool limited = false, int maxLife = 0);

  void setComponent(Grid* component);

  virtual bool move(Biquadris::Direction direction) override;
  virtual int checkRowCompleteness() override;
  virtual std::vector<std::vector<Square>> getPlayerChunk() override;
};

#endif
