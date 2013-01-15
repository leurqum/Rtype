#include "../include/Bullet.hpp"


Bullet::Bullet(int unit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_drawable type) : MovingObstacle(speed, id, rec, strength, isDestroyable)
{
  _unit = unit;
  _type = type;
}


int Bullet::getUnit()const
{
  return (_unit);
}

Protocol::type_drawable Bullet::getType()const
{
  return (_type);
}

void Bullet::update(double time)
{
  // if (type == Protocol::LINEAR)  
  // deplacement de la bullet lineaire
  // else if (type == Protocol::RAYON_LINEAR)
  // deplacement de la bullet d'un autre maniere
}
