#include "LifePowerUp.hpp"

LifePowerUp::~LifePowerUp(void)
{
}

void LifePowerUp::applyToUnit(Unit *u)
{
  int health;

  health = u->getHealth();
  u->setHealth(health + _nb_life);
}
