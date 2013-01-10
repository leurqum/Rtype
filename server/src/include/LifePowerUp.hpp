#ifndef __LIFEPOWERUP__
#define __LIFEPOWERUP__

#include "Obstacle.hpp"
#include "Unit.hpp"

class LifePowerUp : public Obstacle
{
private :
  int _nb_life;
public :
  LifePowerUp(int nb_life, int id, ICollisionDefinition *rec, int strength, bool isDestroyable) : Obstacle(id, rec, strength, isDestroyable) {_nb_life = nb_life;}
  ~LifePowerUp(void);
  void applyToUnit(Unit *u);
};

#endif
