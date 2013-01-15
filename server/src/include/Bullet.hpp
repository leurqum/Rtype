#ifndef __BULLET__
#define __BULLET__

#include "MovingObstacle.hpp"
#include "../../../protocol.h"

class Bullet : public MovingObstacle
{
protected : 
  int _unit;
  Protocol::type_drawable _type;
public:
  Bullet(int unit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_drawable type);
  int getUnit()const;
  void update(double time);
  Protocol::type_drawable getType()const;

};

#endif

