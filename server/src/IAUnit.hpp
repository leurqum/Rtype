#ifndef __IAUNIT__
#define __IAUNIT__

#include "Unit.hpp"

class IAUnit : public Unit
{
public:
  IAUnit(std::pair<float, float> speed, IWeapon *w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable) : Unit(speed, w, id, rec, health, strength, isDestroyable){}
  ~IAUnit(void);
  void takeDecision();
  void executeDecision();
};

#endif
