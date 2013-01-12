#ifndef __BULLET__
#define __BULLET__

#include "MovingObstacle.hpp"
#include "../../../protocol.h"

class Bullet : public MovingObstacle
{
protected : 
  int _unit;
  Protocol::type_bullet _type;
public:
  Bullet(int unit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_bullet type);
  int getUnit()const;
  void update(double time);
  Protocol::type_bullet getType()const;

};

#endif

