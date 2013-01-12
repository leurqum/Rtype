#ifndef __UNIT__
#define __UNIT__

#include "MovingObstacle.hpp"
#include "BasicWeapon.hpp"

class Unit : public MovingObstacle
{
protected : 
  IWeapon *_w;
  int _health;
public :
  Unit(std::pair<float, float> speed, IWeapon * w, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable) : MovingObstacle(speed, id, rec, strength, isDestroyable)
  {
    _w = w;
    _health = health;
  }

  IWeapon *getWeapon();
  int getHealth()const;
  void setHealth(int health);
};

#endif

