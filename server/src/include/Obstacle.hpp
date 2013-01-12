#ifndef __OBSTACLE__
#define __OBSTACLE__

#include "ICollisionDefinition.hpp"

class Obstacle
{
private:
  int			_id;
  ICollisionDefinition*	_rectangle;
  int			_strength;
  bool			_isDestroyable;
public:
  Obstacle(int id, ICollisionDefinition *rec, int strength, bool isDestroyable);
  void update(Obstacle *o);
  int getId()const;
  ICollisionDefinition* getDefinition()const;
  int getStrength()const;
  void setStrength(int strength);
  bool isDestroyable()const;
  void setDestroyable(bool isDestroyable);
  std::pair<float, float> getPosition()const;
  float getPositionX()const;
  float getPositionY()const;
  float getHeight()const;
  float getWidth()const;
};

#endif

