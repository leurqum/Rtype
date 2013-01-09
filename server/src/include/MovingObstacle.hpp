#ifndef __MOVINGOBSCACLE__
#define __MOVINGOBSCACLE__

#include "Obstacle.hpp"

class MovingObstacle: public Obstacle
{
private:
  std::pair<float, float> _speed;
public:
  MovingObstacle(std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable) : Obstacle(id, rec, strength, isDestroyable) {_speed = speed;}
  MovingObstacle(void);
  ~MovingObstacle(void);
  virtual void update();
  std::pair<float, float> getSpeed() const;
};

#endif
