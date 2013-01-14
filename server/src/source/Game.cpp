#include "../include/Game.hpp"
#include <unistd.h>
#include <string>
#include <time.h>

Game::Game(int id)
{
  _id = id;
}

void Game::loop()
{
  clock_t init;
  double time = 0;

  init = clock();
  while (1)
    {
      collision();
      update(time);
      time = 10 * (double)(clock() - init) / (double)CLOCKS_PER_SEC;
      std::cout<<time<<std::endl;
      usleep(100);
    }
  
}

void Game::update(double time)
{
  createRandomObs(time);
  createRandomBonus(time);
  createRandomEnemie(time);

  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    (*it)->update(time);
  
  for (std::list<HumainUnit*>::iterator it = humanList.begin(); it != humanList.end(); it++)
    (*it)->update(time);

  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    (*it)->update(time);
}

void Game::collision()
{
  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    if (collisionIaWithBullet((*it)) == true)
      eraseIa((*it)->getId());
  
  for (std::list<HumainUnit*>::iterator it = humanList.begin(); it != humanList.end(); it++)
    collisionHumainWithBullet((*it));
  
  for (std::list<HumainUnit*>::iterator it = humanList.begin(); it != humanList.end(); it++)
    collisionWithEnemie((*it));

  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    if (collisionBWithObs((*it)) == true)
      eraseBullet((*it)->getId());
  
  for (std::list<HumainUnit*>::iterator it = humanList.begin(); it != humanList.end(); it++)
    collisionWithBonus((*it));
}

IAUnit* Game::createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable, Protocol::type_enemie type)
{
  IAUnit *u = new IAUnit(speed, type, id, coll, health, strength, isDestroyable, this);
  
  iaList.push_back(u);
  return (u);
}

HumainUnit* Game::createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Player *p)
{
  std::pair<float, float> pos(0, 0);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 2, 2);
  HumainUnit *h = new HumainUnit(speed, p, id, coll, health, strength, isDestroyable, this);

  humanList.push_back(h);
  return (h);
}

MovingObstacle* Game::createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable)
{
  MovingObstacle* l = new MovingObstacle(speed, id, coll, strength, isDestroyable);
 
  obsList.push_back(l);
  return (l);
}

Player* Game::createPlayer(int id, std::string name, int life, ISocket *tcp, ISocket *udp)
{
  Player* p = new Player(id, name, life, tcp, udp);

  playerList.push_back(p);
  return (p);
}

LifePowerUp* Game::createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, int strength)
{
  LifePowerUp* l = new LifePowerUp(nb_life, id, coll, strength, isDestroyable);

  bonusList.push_back(l);
  return (l);
}

Bullet *Game::createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_bullet type)
{
  
  Bullet *b = new Bullet(idUnit, speed, id, rec, strength, isDestroyable, type);

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

  createHumainUnit(humanList.size(), std::pair<float, float>(1, 1), 3, 1, true, p);
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
  return (_id);
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
	  eraseIa((*it)->getId());
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
	  eraseObs((*it)->getId());
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
 
  createBullet(id, std::pair<float, float>(1, 1), bulletList.size(), coll, 1, true, Protocol::LINEAR);
}

void Game::fire_ia(int id)
{
  IAUnit *u = getUnitAI(id);
  
  if (u == NULL)
    return;
  
  ICollisionDefinition *coll;

  if (u->getType() == Protocol::EASY)
    {
      coll = new RectangleCollisionDefinition(u->getPosition(), 1, 1);
      createBullet(id, std::pair<float, float>(1, 1), bulletList.size(), coll, 1, true, Protocol::LINEAR);
    }    
  else if (u->getType() == Protocol::HARD)
    {
      coll = new RectangleCollisionDefinition(u->getPosition(), 50, 1);
      createBullet(id, std::pair<float, float>(1, 1), bulletList.size(), coll, 1, true, Protocol::RAYON_LINEAR);
    }
}

void Game::move(int id)
{
  Unit *u = getUnit(id);
  
  if (u == NULL)
    return;
  if (collisionUWithObs(u) == false)
    u->getDefinition()->move();
}

int Game::getSizeGame()const
{
  return (iaList.size() + humanList.size() + bulletList.size() + obsList.size() + bonusList.size());
}

void Game::createRandomObs(double time)
{
}

void Game::createRandomBonus(double time)
{
}

void Game::createRandomEnemie(double time)
{
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
      Protocol::drawable_bullet * d = new Protocol::drawable_bullet(); 
      
      memset(d, 0, sizeof(Protocol::drawable_bullet *));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();
      d->bullet = (*it)->getType();
      memcpy(&res + position, d, sizeof(Protocol::drawable_bullet*));
      position += sizeof(Protocol::drawable_bullet*);
    }

  for (std::list<IAUnit*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      Protocol::drawable_enemie * d = new Protocol::drawable_enemie(); 
      
      memset(d, 0, sizeof(Protocol::drawable_enemie *));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->xPosition = (*it)->getPositionY();
      d->enemie = (*it)->getType();
      memcpy(&res + position, d, sizeof(Protocol::drawable_enemie*));
      position += sizeof(Protocol::drawable_enemie*);
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
