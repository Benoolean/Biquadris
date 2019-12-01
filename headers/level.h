#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "player.h"
#include "blockgrid.h"
#include "effect.h"
#include "window.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Xwindow;

class Level {
  int level;

  Xwindow* window;
  bool enableGraphics;

  std::ostream* out;

  std::vector<Player*> players;
  int currentPlayer;

  static int highScore;

  //These effects stack for each turn
  //When a user applies an effect, it is stacked on top of the next
  //grid. The current effect is set to the topmost effect, otherwise nullptr.
  //After every turn the effects are deleted.
  std::vector<Effect*> effects;
  Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

  bool over; //True for over, false for not over
  unsigned int winner; // Undefined behaviour unless isOver flag is set

  void changePlayer(int player);

  void checkFullLine(); //Used to determine if there is a full line (also updates players' score)

  void print(std::string s);

public:
  Level(const int level = 0,
        const int numPlayers = 2,
        std::vector<std::string> source = std::vector<std::string>(),
        std::ostream* out = nullptr, Xwindow* window = nullptr);
  ~Level();

  void increaseLevel(); //Increases level by 1 up to 4
  void lowerLevel(); //Decreases level by 1 down to 0

  bool changeActive(Block* newActive); //Will be used for force and after each drop

  void rotateClockwise();
  void rotateCClockwise();

  void shiftX(int shift);
  void shiftY(unsigned int shift);

  void drop();

  void setRandom();
  void setNotRandom(std::string source);

  void blind();  

  bool isOver() const;

  int getWinner() const; //Returns -1 if isOver flag is not set

  static int getHighScore();
};

#endif
