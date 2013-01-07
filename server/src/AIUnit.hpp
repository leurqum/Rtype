#ifndef __AIUNIT__
#define __AIUNIT__

#include "Unit.hpp"

class AIUnit : public Unit
{
public:
  AIUnit(std::pair<float, float> speed, IWeapon *w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable) : Unit(speed, w, id, rec, health, strength, isDestroyable){}
  ~AIUnit(void);
  void takeDecision();
  void executeDecision();
};

#endif
