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

void IAUnit::paternSolo(int time)
{

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
	
	else
		{
			if ((int)time % cadence == 0)
				this->_toShoot = true;
			else
			{
				this->_toShoot = false;
				chooseDirection(time);
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
