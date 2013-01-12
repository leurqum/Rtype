#ifndef __IAUNIT__
#define __IAUNIT__

#include "Unit.hpp"
#include "Game.hpp"

class IAUnit : public Unit
{
  Game *_game;
public:
  IAUnit(std::pair<float, float> speed, IWeapon *w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable, Game *game) : Unit(speed, w, id, rec, health, strength, isDestroyable){ _game = game;}
  ~IAUnit(void);
  void takeDecision();
  void executeDecision();
};

#endif
