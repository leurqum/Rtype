#include "../include/IAUnit.hpp"


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

void IAUnit::chooseDirection()
{
	//if (this->_patern == 1)
	//{

	//}
}
void IAUnit::takeDecision(double time)
{
	int		cadence = 3;

	if (time > 45)
		cadence = 2;

	if (this->_patern == 0 && (int)time % 4 == 0)
		this->_toShoot = true;
	
	else
		{
			if ((int)time % cadence == 0)
				this->_toShoot = true;
			else
			{
				this->_toShoot = false;
				chooseDirection();
			}
		}
}

void IAUnit::executeDecision()
{
	if (this->_toShoot == true)
		this->_game->fire(this->getId());
	else
		this->_game->move(this->getId(),&(this->_direction));

}
