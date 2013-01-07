#ifndef __RECTANGLECOLLDEF__
#define __RECTANGLECOLLDEF__

#include "ICollisionDefinition.hpp"
#include <utility>

class RectangleCollisionDefinition : public ICollisionDefinition
{
private:
  std::pair<float, float>	_position;
  float		      		_height;
  float				_width;
  
public:
  RectangleCollisionDefinition(std::pair<float, float>position,int height,int width);
  virtual bool isCollidingWith();
  virtual std::pair<float, float> getPosition()const;
  virtual void setCollisionFilter(int filter);
  virtual void move();
  void setPosition(std::pair<float, float>position);
  float getHeight()const;
  void setHeight(float height);
  float getWidth()const;
  void setWidth(float width);
  
};

#endif
