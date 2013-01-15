#include "../include/RectangleCollisionDefinition.hpp"

RectangleCollisionDefinition::RectangleCollisionDefinition(std::pair<float, float>position, int height, int width)
{
  _position = position;
  _height = height;
  _width = width;
}

bool RectangleCollisionDefinition::isCollidingWith()
{
  return true;
}

void RectangleCollisionDefinition::setCollisionFilter(int filter)
{
  (void)filter;
}

std::pair<float, float> RectangleCollisionDefinition::getPosition()const
{
  return (_position);
}

void RectangleCollisionDefinition::setPosition(std::pair<float, float>position)
{
  _position = position;
}

float RectangleCollisionDefinition::getHeight()const
{
  return (_height);
}

void RectangleCollisionDefinition::setHeight(float height)
{
  _height = height;
}

float RectangleCollisionDefinition::getWidth()const
{
  return (_width);
}

void RectangleCollisionDefinition::setWidth(float width)
{
  _width = width;
}

void RectangleCollisionDefinition::move(Protocol::move *m)
{
  std::pair<float, float>position = _position;
  position.second = (m->top == 1) ?  position.second + 0.2 : position.second;
  position.first = (m->right == 1) ? position.first + 0.2 : position.first;
  position.second = (m->down == 1) ?  position.second - 0.2 : position.second;
  position.first = (m->left == 1) ?  position.first - 0.2 : position.first;

  setPosition(position);
}
