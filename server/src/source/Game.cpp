#include "../include/Game.hpp"
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
	(this->*_fcts[_cmd->_cmds[i].first])(_cmd->_cmds[i].second);
      _cmd->removeCommands();
    }
}

IAUnit* Game::createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable, Game *game)
{
  IWeapon *w = new BasicWeapon();
  IAUnit *u = new IAUnit(speed, w, id, coll, health, strength, isDestroyable);
  
  //WARING GAME
  (void)game;
  iaList.push_back(u);
  return (u);
}

HumainUnit* Game::createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Game *game, Player *p)
{
  IWeapon *w = new BasicWeapon();
  std::pair<float, float> pos(0, 0);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 2, 2);
  HumainUnit *h = new HumainUnit(speed, p, w, id, coll, health, strength, isDestroyable);
  //WARING GAME
  (void)game;
  humanList.push_back(h);
  return (h);
}

MovingObstacle* Game::createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable, Game *game)
{
  MovingObstacle* l = new MovingObstacle(speed, id, coll, strength, isDestroyable);
  //WARING GAME
  (void)game;
  obsList.push_back(l);
  return (l);
}

Player* Game::createPlayer(int id, std::string name, int life, ISocket *tcp, ISocket *udp)
{
  Player* p = new Player(id, name, life, tcp, udp);

  playerList.push_back(p);
  return (p);
}

LifePowerUp* Game::createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, Game *game, int strength)
{
  LifePowerUp* l = new LifePowerUp(nb_life, id, coll, strength, isDestroyable);

  //WARING GAME
  (void)game;

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

IAUnit *Game::getUnitAI(int id)const
{
    for (std::list<IAUnit*>::const_iterator it = iaList.begin(); it != iaList.end(); it++)
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

void Game::addPlayer(std::string name, ISocket *udp, ISocket *tcp)
{
  Player *p = createPlayer(playerList.size(), name, 3, tcp, udp);

  createHumainUnit(humanList.size(), std::pair<float, float>(1, 1), 3, 1, true, this, p);
}

int Game::getNbPlayer()const
{
  return (humanList.size());
}

Player *Game::getPlayerBySockTcp(ISocket *sock)const
{
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getSocketTcp() == sock)
	return (*it);
    }
  return (NULL);
}

Player *Game::getPlayerBySockUdp(ISocket *sock)const
{
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getSocketUdp() == sock)
	return (*it);
    }
  return (NULL);
}

int Game::getId()const
{
  return (id);
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
  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
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

bool Game::isFriendlyBullet(Bullet *b)
{
  if (getUnitHuman(b->getUnit()) != NULL)
    return (true);
  return (false);
}

bool Game::collisionHumainWithBullet(HumainUnit *u)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if (isFriendlyBullet(*it) == true)
	return (false);
      float y = u->getPositionY();
      float x = u->getPositionX();
      float obsY = (*it)->getPositionY();
      float obsX = (*it)->getPositionX();
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  u->setHealth(u->getHealth() - 1);
	  eraseBullet((*it)->getId());
	  return (true);
	}
    }
  return (false);	
}

bool Game::collisionIaWithBullet(IAUnit *u)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if (isFriendlyBullet(*it) != true)
	return (false);
      float y = u->getPositionY();
      float x = u->getPositionX();
      float obsY = (*it)->getPositionY();
      float obsX = (*it)->getPositionX();
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  eraseBullet((*it)->getId());
	  eraseIa(u->getId());
	  return (true);
	}
    }
  return (false);	
}

bool Game::collisionWithEnemie(HumainUnit *u)
{
  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      float y = u->getPositionY();
      float x = u->getPositionX();
      float iaY = (*it)->getPositionY();
      float iaX = (*it)->getPositionX();
      if ((y + u->getHeight() > iaY
	   && y < iaY + (*it)->getHeight()) &&
	  (x + u->getWidth() > iaX &&
	   x < iaX + (*it)->getWidth()))
	{
	  u->setHealth(0);
	  return (true);
	}
    }
  return (false);
}

bool Game::collisionUWithObs(Unit *u)
{
  for (std::list<MovingObstacle*>::iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      float y = u->getPositionY();
      float x = u->getPositionX();
      float mObsY = (*it)->getPositionY();
      float mObsX = (*it)->getPositionX();
      if ((y + u->getHeight() > mObsY
	   && y < mObsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > mObsX &&
	   x < mObsX + (*it)->getWidth()))
	return (true);
    }
  return (false);
}

bool Game::collisionBWithObs(Bullet *b)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      float y = b->getPositionY();
      float x = b->getPositionX();
      float mObsY = (*it)->getPositionY();
      float mObsX = (*it)->getPositionX();
      if ((y + b->getHeight() > mObsY
	   && y < mObsY + (*it)->getHeight()) &&
	  (x + b->getWidth() > mObsX &&
	   x < mObsX + (*it)->getWidth()))
	{
	  eraseBullet(b->getUnit());
	  return (true);
	}
    }
  return (false);
}

bool Game::collisionWithBonus(HumainUnit *u)
{
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      float y = u->getPositionY();
      float x = u->getPositionX();
      float bY = (*it)->getPositionY();
      float bX = (*it)->getPositionX();
      if ((y + u->getHeight() > bY
	   && y < bY + (*it)->getHeight()) &&
	  (x + u->getWidth() > bX &&
	   x < bX + (*it)->getWidth()))
	{
	  (*it)->applyToUnit(u);
	  eraseBonus((*it)->getId());
	  return true;
	}
    }
  return (false);
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

int Game::getSizeGame()const
{
  return (iaList.size() + humanList.size() + bulletList.size() + obsList.size() + bonusList.size());
}

void *Game::formatGameSend()
{
  Protocol::package *pac = new Protocol::package();
  void *res;
  int position = 0;

  memset(pac, 0, sizeof(Protocol::package*));
  pac->id = Protocol::SEND_WORLD;
  pac->size = sizeof(Protocol::package*) + (sizeof(Protocol::monde_param*) * this->getSizeGame());
 
  memset(res, 0, pac->size);
  memcpy(res, pac, sizeof(Protocol::package*));
  position += sizeof(Protocol::package*);
  
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      
      memset(d, 0, sizeof(Protocol::drawable *));
      d->id = (*it)->getId();
      d->type = Protocol::BULLET;
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();       
      memcpy(&res + position, d, sizeof(Protocol::drawable*));
      position += sizeof(Protocol::drawable*);
    }

  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      
      memset(d, 0, sizeof(Protocol::drawable *));
      d->id = (*it)->getId();
      d->type = Protocol::MONSTER;
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();       
      memcpy(&res + position, d, sizeof(Protocol::drawable*));
      position += sizeof(Protocol::drawable*);
    }

for (std::list<HumainUnit*>::const_iterator it = humanList.begin(); it != humanList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      
      memset(d, 0, sizeof(Protocol::drawable *));
      d->id = (*it)->getId();
      d->type = Protocol::SHIP;
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();       
      memcpy(&res + position, d, sizeof(Protocol::drawable*));
      position += sizeof(Protocol::drawable*);
    }

for (std::list<MovingObstacle*>::const_iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      
      memset(d, 0, sizeof(Protocol::drawable *));
      d->id = (*it)->getId();
      d->type = Protocol::OBSTACLE;
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();       
      memcpy(&res + position, d, sizeof(Protocol::drawable*));
      position += sizeof(Protocol::drawable*);
    }
 
 for (std::list<LifePowerUp*>::const_iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      
      memset(d, 0, sizeof(Protocol::drawable *));
      d->id = (*it)->getId();
      d->type = Protocol::BONUS;
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();       
      memcpy(&res + position, d, sizeof(Protocol::drawable*));
      position += sizeof(Protocol::drawable*);
    } 
 return (res);
}
