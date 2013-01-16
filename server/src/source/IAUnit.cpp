#include "../include/IAUnit.hpp"


IAUnit::IAUnit(std::pair<float, float> speed, Protocol::type_drawable type, int id, ICollisionDefinition *rec
	  , int health, int strength, bool isDestroyable, Game *game, Protocol::patern_enemie patern)
  : Unit(speed, id, rec, health, strength, isDestroyable)
{ 
  _game = game;
  _type = type; 
  _patern = patern; 
  _toShoot = false;
  _canShoot = false;
  
  if (patern != 4 && patern != 5)
    {
      this->_direction.left = 1;
      this->_direction.top = 0;
      this->_direction.down = 0;
      this->_direction.right = 0;
      if (patern != 6)
	this->_canShoot = true;
    }
  else
    {
      this->_direction.left = 0;
      this->_direction.top = 0;
      this->_direction.down = 1;
      this->_direction.right = 0;
    }
};

IAUnit::~IAUnit(void)
{
}



Protocol::type_drawable IAUnit::getType()const
{
  return (_type);
}

Protocol::patern_enemie IAUnit::getPatern()const
{
	return (_patern);
}

void IAUnit::update(double time)
{
		takeDecision(time);
		executeDecision();
}

void IAUnit::paternSolo(int time)
{
  this->_direction.left = 1;
}

void IAUnit::paternPack(int time)
{
	if (time % 3 == 0)
		{
			if (this->getPositionY() >= 0 || this->_direction.top == 1)
			{
				this->_direction.top = 0;
				this->_direction.down = 1;
			}
			
			if (this->getPositionY() <= YMAX || this->_direction.down == 1)
			{
				this->_direction.top = 1;
				this->_direction.down = 0;
			}
		}
}

void IAUnit::paternLineToDiago(int time)
{
	if (this->getPositionX() < XMAX / 2)
	{
		if (this->_patern == 5)
			this->_direction.down = 1;
		else
			this->_direction.top = 1;

		this->_canShoot = true;
	}
}

void IAUnit::chooseDirection(double time)
{
  if (this->_patern == 1)
    paternSolo(time);
  else if (this->_patern == 2)
    paternPack(time);
  else if (this->_patern == 4 || this->_patern == 5)
    paternLineToDiago(time);
}

void IAUnit::takeDecision(double time)
{
	int		cadence = 3;

	if (time > 45)
		cadence = 2;

	if (this->_patern == 0 && (int)time % 4 == 0)
		this->_toShoot = true;
	
	// else
	// 	{
	// 		if ((int)time % cadence == 0 && this->_canShoot == true)
	// 			this->_toShoot = true;
	// 		else
	// 		{
	// 			this->_toShoot = false;
	// 			chooseDirection(time);
	// 		}
	// 	}
	chooseDirection(time);
}

void IAUnit::executeDecision()
{
	// if (this->_toShoot == true)
	// 	this->_game->fire_ia(this->getId());
	// else
	this->_game->moveIa(this->getId(),&(this->_direction));
}
