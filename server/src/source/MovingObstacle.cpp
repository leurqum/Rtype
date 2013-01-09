#include "../include/MovingObstacle.hpp"

MovingObstacle::~MovingObstacle(void)
{
}

void MovingObstacle::update()
{
}

std::pair<float, float> MovingObstacle::getSpeed() const
{
  return (_speed);
}
