#include "../include/Unit.hpp"

Unit::Unit(std::pair<float, float> speed, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable) : MovingObstacle(speed, id, rec, strength, isDestroyable)
{
  _health = health;
}

void Unit::setHealth(int health)
{
  _health = health;
}

int Unit::getHealth()const
{
  return (_health);
}
