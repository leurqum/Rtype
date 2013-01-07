#ifndef __ICOLLISIONDEF__
#define __ICOLLISIONDEF__

#include <utility>

class ICollisionDefinition
{
public:
  virtual bool isCollidingWith() = 0;
  virtual std::pair<float, float> getPosition()const = 0;
  virtual void setCollisionFilter(int filter) = 0;
  virtual void move() = 0;
};

#endif
