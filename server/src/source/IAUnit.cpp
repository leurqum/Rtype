#include "../include/IAUnit.hpp"

IAUnit::~IAUnit(void)
{
}

Protocol::type_enemie IAUnit::getType()const
{
  return (_type);
}

void IAUnit::update(double time)
{
}

void IAUnit::takeDecision()
{
  //utiliser move et fire_ia qui se trouve dans game
}

void IAUnit::executeDecision()
{
}