#include "Obstacle.hpp"

Obstacle::Obstacle(int id, ICollisionDefinition *rec, int strength, bool isDestroyable)
{
  _id = id;
  _rectangle = rec;
  _strength = strength;
  _isDestroyable = isDestroyable; 
}

float Obstacle::collision(Obstacle *o)
{
  return 0;
}
float Obstacle::internalCollision(Obstacle *o)
{
  return 0;
}

void Obstacle::update(Obstacle *o)
{
}

int Obstacle::getId()const
{
  return (_id);
}

ICollisionDefinition* Obstacle::getDefinition()const
{
  return (_rectangle);
}

int Obstacle::getStrength()const
{
  return (_strength);
}

void Obstacle::setStrength(int strength)
{
  _strength = strength;
}

bool Obstacle::isDestroyable()const
{
  return (_isDestroyable);
}

void Obstacle::setDestroyable(bool isDestroyable)
{
  _isDestroyable = isDestroyable;
}

float Obstacle::getPostionX()const
{
  return (_rectangle->getPosition().first);
}

float Obstacle::getPostionY()const
{
  return (_rectangle->getPosition().first);
}

float Obstacle::getHeight()const
{
  return (_rectangle->getHeight());
}

float Obstacle::getWidth()const
{
  return (_rectangle->getWidth());
}    
