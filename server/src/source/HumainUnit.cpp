#include "../include/HumainUnit.hpp"

HumainUnit::~HumainUnit(void)
{
}

Player *HumainUnit::getPlayer()const
{
  return (_p);
}

void HumainUnit::update(double time)
{
  if (this->getHealth() <= 0)
    this->_type = Protocol::DEAD;
}

Protocol::type_drawable HumainUnit::getType()const
{
  return (_type);
}
