#ifndef __HUMAINUNIT__
#define __HUMAINUNIT__

#include "Unit.hpp"
#include "Player.hpp"

class HumainUnit : public Unit
{
private:
  Player *_p;
public:
  HumainUnit(std::pair<float, float> speed, Player *p, IWeapon *w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable) : Unit(speed, w, id, rec, health, strength, isDestroyable){_p = p;}
  ~HumainUnit(void);
  Player *getPlayer()const;
};

#endif
