#include "../headers/blind.h"
using namespace std;

Blind::Blind(Grid* component) : Effect(component, true, 1) { }

vector<vector<Square>> Blind::getPlayerChunk() {
  if(life > 0) {
    std::vector<std::vector<Square>> chunk = component->getPlayerChunk();
    for(int i = 0; i < (int)chunk.size(); i++) {
      for(int j = 0; j < (int)chunk[i].size(); j++) {
        if(i >= 2 && i <= 11 && j >= 2 && j <= 8) {
          chunk[i][j].symbol = '?';
          chunk[i][j].colour = 1;
          chunk[i][j].status = SquareStatus::INACTIVE;
        }
      }
    }
    return chunk;
  }
  else return component->getPlayerChunk();
}
