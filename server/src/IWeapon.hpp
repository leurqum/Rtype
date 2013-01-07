#ifndef __IWEAPON__
#define __IWEAPON__

#include "Bullet.hpp"

class IWeapon
{
public:
  virtual void fire(Bullet *b) = 0;
  //virtual void update() = 0;
};

#endif
