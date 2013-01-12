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
  if (this->getHealth() == 0)
    _game->eraseHumain(this->getId());
}
