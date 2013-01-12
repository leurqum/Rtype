#ifndef __UNIT__
#define __UNIT__

#include "MovingObstacle.hpp"

class Unit : public MovingObstacle
{
protected : 
  int _health;
public :
  Unit(std::pair<float, float> speed, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable);
  int getWeapon();
  int getHealth()const;
  void setHealth(int health);
};

#endif

