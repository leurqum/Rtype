#ifndef __HUMAINUNIT__
#define __HUMAINUNIT__

#include "Unit.hpp"
//#include "Player.hpp"
#include "Game.hpp"

class HumainUnit : public Unit
{
private:
  //  Player *_p;
  int _idPlayer;
  Game *_game;
  Protocol::type_drawable _type;
public:
  HumainUnit(std::pair<float, float> speed, int idPlayer, int id, ICollisionDefinition *rec, int health, int strength, bool isDestroyable, Game *game) : Unit(speed, id, rec, health, strength, isDestroyable)
  {
    _idPlayer = idPlayer;
    _game = game;
    _type = Protocol::SHIP;
  }
  ~HumainUnit(void);
  //Player *getPlayer()const;
  int getPlayerId()const;
  void update(double time);
  Protocol::type_drawable getType()const;
};

#endif
