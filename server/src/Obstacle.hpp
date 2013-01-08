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
  float collision(Obstacle *o);
  float internalCollision(Obstacle *o);
  void update(Obstacle *o);
  int getId()const;
  ICollisionDefinition* getDefinition()const;
  int getStrength()const;
  void setStrength(int strength);
  bool isDestroyable()const;
  void setDestroyable(bool isDestroyable);
  float getPostionX()const;
  float getPostionY()const;
  float getHeight()const;
  float getWidth()const;
};

#endif