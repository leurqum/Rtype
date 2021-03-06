#ifndef __ICOLLISIONDEF__
#define __ICOLLISIONDEF__

#include <utility>
#include "./../../../protocol.h"

class ICollisionDefinition
{
public:
  virtual bool isCollidingWith() = 0;
  virtual std::pair<float, float> getPosition()const = 0;
  virtual void setCollisionFilter(int filter) = 0;
  virtual void move(Protocol::move *m, int speed) = 0;
  virtual float getWidth()const = 0;
  virtual float getHeight()const = 0;
};

#endif
