#ifndef __BULLET__
#define __BULLET__

#include "MovingObstacle.hpp"

class Bullet : public MovingObstacle
{
protected : 
  int _idUnit;
public:
  Bullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable) : MovingObstacle(speed, id, rec, strength, isDestroyable) {_idUnit = idUnit;}
  int getUnit()const;
};

#endif
