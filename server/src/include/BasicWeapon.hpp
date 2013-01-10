#ifndef __WEAPON__
#define __WEAPON__

#include "IWeapon.hpp"

class BasicWeapon : public IWeapon
{
public:
  virtual void fire(Bullet *b);
};

#endif
