#ifndef __HUMAINUNIT__
#define __HUMAINUNIT__

#include "Unit.hpp"
#include "Player.hpp"
#include "Game.hpp"

class HumainUnit : public Unit
{
private:
  Player *_p;
  Game *_game;
public:
  HumainUnit(std::pair<float, float> speed, Player *p, IWeapon *w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable, Game *game) : Unit(speed, w, id, rec, health, strength, isDestroyable){_p = p; _game = game;}
  ~HumainUnit(void);
  Player *getPlayer()const;
};

#endif
