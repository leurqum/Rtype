#include "Game.hpp"
#include <string>

Game::Game()
{
  _fcts[0] = &Game::fire;
  _fcts[1] = &Game::move;
  _cmd = new CommandManager(this);
}

void Game::loop()
{
  while (1)
    {
      for (unsigned int i = 0; i < _cmd->_cmds.size(); i++)
	(this->*_fcts[_cmd->_cmds[i].second])(_cmd->_cmds[i].second);
      _cmd->removeCommands();
    }
}

AIUnit* Game::createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable, Game *game)
{
  IWeapon *w = new BasicWeapon();
  AIUnit *u = new AIUnit(speed, w, id, coll, health, strength, isDestroyable);

  iaList.push_back(u);
  return (u);
}

HumainUnit* Game::createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Game *game, Player *p)
{
  IWeapon *w = new BasicWeapon();
  std::pair<float, float> pos(0, 0);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 2, 2);
  HumainUnit *h = new HumainUnit(speed, p, w, id, coll, health, strength, isDestroyable);
  
  humanList.push_back(h);
  return (h);
}

MovingObstacle* Game::createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable, Game *game)
{
  MovingObstacle* l = new MovingObstacle(speed, id, coll, strength, isDestroyable);

  obsList.push_back(l);
  return (l);
}

Player* Game::createPlayer(int id, std::string name, int life)
{
  Player* p = new Player(id, name, life);

  playerList.push_back(p);
  return (p);
}

LifePowerUp* Game::createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, Game *game, int strength)
{
  LifePowerUp* l = new LifePowerUp(nb_life, id, coll, strength, isDestroyable);

  bonusList.push_back(l);
  return (l);
}

Bullet *Game::createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable)
{
  Bullet *b = new Bullet(idUnit, speed, id, rec, strength, isDestroyable);

  bulletList.push_back(b);
  return (b);
}

Bullet *Game::getBullet(int id)const
{
  for (std::list<Bullet*>::const_iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

HumainUnit *Game::getUnitByPlayer(Player *p)const
{
    for (std::list<HumainUnit*>::const_iterator it = humanList.begin(); it != humanList.end(); it++)
    {
      if ((*it)->getPlayer() == p)
	return (*it);
    }
  return NULL;
}
 
HumainUnit *Game::getUnitHuman(int id)const
{
  for (std::list<HumainUnit*>::const_iterator it = humanList.begin(); it != humanList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

AIUnit *Game::getUnitAI(int id)const
{
    for (std::list<AIUnit*>::const_iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

Unit *Game::getUnit(int id)const
{
  Unit *u;

  if ((u = getUnitHuman(id)) != NULL)
    return (u);
  else if ((u = getUnitAI(id)) != NULL)
    return (u);
  return (NULL);
}

MovingObstacle *Game::getObs(int id)const
{
  for (std::list<MovingObstacle*>::const_iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}
 
LifePowerUp *Game::getLifePowerUp(int id)const
{
  for (std::list<LifePowerUp*>::const_iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

Player *Game::getPlayer(int id)const
{
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

void Game::addPlayer(std::string name)
{
  Player *p = createPlayer(playerList.size(), name, 3);

  createHumainUnit(humanList.size(), std::pair<float, float>(1, 1), 3, 1, true, this, p);
}

int Game::getNbPlayer()const
{
  return (humanList.size());
}

void Game::eraseBullet(int id)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  bulletList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::eraseBulletsPlayer(int idPlayer)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if ((*it)->getUnit() == idPlayer)
	bulletList.erase(it);
      else
	it++;
    }
}

//WARNING !!!!!!!!!!!!!!!!!!!!!!!
void Game::erasePlayer(int id)
{
  for (std::list<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  playerList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::eraseHumain(int id)
{
  for (std::list<HumainUnit*>::iterator it = humanList.begin(); it != humanList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  humanList.erase(it);
	  erasePlayer(getPlayer((*it)->getId())->getId());
	  eraseBulletsPlayer((*it)->getId());
	  return;
	}
      else
	it++;
    }
}

void Game::eraseIa(int id)
{
  for (std::list<AIUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  iaList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::eraseObs(int id)
{
  for (std::list<MovingObstacle*>::iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  obsList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::eraseBonus(int id)
{
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  bonusList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::fire(int id)
{
  Unit *u = getUnit(id);
  
  if (u == NULL)
    return;
  
  std::pair<float, float> pos(0, 0);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 2, 2);
  Bullet *b = createBullet(id, std::pair<float, float>(1, 1), bulletList.size(), coll, 1,true);
  
  u->getWeapon()->fire(b);
}

void Game::move(int id)
{
  Unit *u = getUnit(id);
  
  if (u == NULL)
    return;

  u->getDefinition()->move();
}
