#ifndef __IAUNIT__
#define __IAUNIT__

#include "Unit.hpp"
#include "Game.hpp"


class IAUnit : public Unit
{
  Game *_game;
  Protocol::type_enemie _type;
public:
  IAUnit(std::pair<float, float> speed, Protocol::type_enemie type, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable, Game *game)
	  : Unit(speed, id, rec, health, strength, isDestroyable){ _game = game; _type = type;}
  ~IAUnit(void);
  void takeDecision();
  void executeDecision();
  void update(double time);
  Protocol::type_enemie getType()const;
};

#endif
