#ifndef __IAUNIT__
#define __IAUNIT__

#include "Unit.hpp"
#include "Game.hpp"

class IAUnit : public Unit
{

public:
  IAUnit(std::pair<float, float> speed, Protocol::type_enemie type, int id, ICollisionDefinition *rec
		, int health, int strength, bool isDestroyable, Game *game, Protocol::patern_enemie patern)
			  : Unit(speed, id, rec, health, strength, isDestroyable)
	{ 
		_game = game;
		_type = type; 
		_patern = patern; 
		_toShoot = false;

		this->_direction.left = 1;
		this->_direction.top = 0;
		this->_direction.down = 0;
		this->_direction.right = 0;
	};
  ~IAUnit(void);
  void takeDecision(double);
  void executeDecision();
  void chooseDirection();
  void update(double time);
  Protocol::type_enemie getType()const;
  Protocol::patern_enemie getPatern() const;
protected:
  Game *_game;
  Protocol::type_enemie _type;
  Protocol::patern_enemie _patern;
  bool _toShoot;
  Protocol::move _direction;
};

#endif
