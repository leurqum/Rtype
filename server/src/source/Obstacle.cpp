#include "../include/Obstacle.hpp"

Obstacle::Obstacle(int id, ICollisionDefinition *rec, int strength, bool isDestroyable)
{
  _id = id;
  _rectangle = rec;
  _strength = strength;
  _isDestroyable = isDestroyable; 
}

void Obstacle::update(Obstacle *o)
{
  (void)o;
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

float Obstacle::getPositionX()const
{
  return (_rectangle->getPosition().first);
}

float Obstacle::getPositionY()const
{
  return (_rectangle->getPosition().first);
}

std::pair<float, float> Obstacle::getPosition()const
{
  return (_rectangle->getPosition());
}

float Obstacle::getHeight()const
{
  return (_rectangle->getHeight());
}

float Obstacle::getWidth()const
{
  return (_rectangle->getWidth());
}    
