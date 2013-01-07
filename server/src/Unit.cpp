#include "Unit.hpp"

IWeapon *Unit::getWeapon()
{
  return (_w);
}

void Unit::setHealth(int health)
{
  _health = health;
}

int Unit::getHealth()const
{
  return (_health);
}
