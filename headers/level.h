#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "blockgrid.h"
#include "effect.h"
#include "window.h"

#include <vector>
#include <string>

#include <map>

class Xwindow;

class Level {
  int level;

  Xwindow* window;
  bool enableGraphics;

  struct Player {
    BlockGrid grid;

    std::string source; //This allows a new stream to be opened once the end of either hase been reached
    std::vector<std::string> sequence; // Pushed from specified fstream, and stack popped every drop

    int points;
  };
  std::vector<Player*> players;
  int currentPlayer;

  static int highScore;

  std::vector<Effect*> effects;
  Effect* currentEffect; // The topmost effect, default is grid if no effect was created last turn

  void togglePlayer();

  bool over; //True for over, false for not over
  unsigned int winner; // Undefined behaviour unless isOver flag is set

  void checkFullLine(); //Used to determine if there is a full line (also updates players' score)

public:
  Level(const int level = 0, const int numPlayers = 2, const std::string* const source = nullptr, Xwindow* window = nullptr);
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

  bool isOver() const;

  int getWinner() const; //Returns -1 if isOver flag is not set

  static int getHighScore();
};

#endif
