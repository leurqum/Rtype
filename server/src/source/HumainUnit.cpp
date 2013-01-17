#include "../include/HumainUnit.hpp"

HumainUnit::~HumainUnit(void)
{
}

int HumainUnit::getPlayerId()const
{
  return (_idPlayer);
}
void HumainUnit::update(double time)
{
  if (this->getHealth() <= 0)
    _game->sendShipErase(this);
}

Protocol::type_drawable HumainUnit::getType()const
{
  return (_type);
}

double HumainUnit::getTimeBullet()const
{
  return _lastBullet;
}

void HumainUnit::setTimeBullet(double time)
{
  _lastBullet = time;
}
