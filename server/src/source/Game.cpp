#include <string>
#include <time.h>
#include <stdio.h>
#include "../include/Game.hpp"

#ifdef __unix__
#include <unistd.h>
#include <sys/time.h>
#include <dlfcn.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#include <sys/timeb.h>

struct timeval
{
  long    tv_sec; 
  long    tv_usec;
};

int gettimeofday (struct timeval *tp, void *tz)
{
  struct _timeb timebuffer;
  _ftime (&timebuffer);
  tp->tv_sec = timebuffer.time;
  tp->tv_usec = timebuffer.millitm * 1000;
  return 0;
}
#endif


Game::Game(int id)
{
  _id = id;
  mutexPlayers = new MyMutex();


	#ifdef __unix__
  void * hndl;
  // Ouverture de la librairie
  hndl = dlopen("./src/lib/ia.so", RTLD_LAZY);
  if(hndl == NULL)
    {
      std::cerr << "dlopen failed" << std::endl; 
      exit(0);
    }
  // Chargement du créateur
  void *mkr = dlsym(hndl, "entry_point");
  if (mkr == NULL)
    {
      std::cerr << "dlsym failed" << std::endl;
      exit(0);
    }
  iaFactory = (maker_Ia)mkr;
	#endif
#ifdef _WIN32



#endif
}

static long myclock()
{
  struct timeval tv; 
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void Game::loop()
{
  srand(time(NULL));
  clock_t init;

  init = myclock();
  t = 0;
  while (1)
    {
      collision();
      checkPlayer();
      update(t);
      sendGame();
      eraseShipOut();
      eraseBulletOut();
      eraseIaOut();
      eraseBonusOut();
      eraseObsOut();
      
#ifdef __unix__
      usleep(20000);
      t = ((long)(myclock() - init) / (long)CLOCKS_PER_SEC);
#endif
#ifdef _WIN32
      Sleep(20);
      t = ((long)(myclock() - init) / (long)CLOCKS_PER_SEC) / 1000;
#endif
    }  
}

void Game::eraseShipOut()
{
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    {
      if ((*it)->getPositionX() > XMAX ||
	  (*it)->getPositionY() > YMAX || 
	  (*it)->getPositionX() < -15 ||
	  (*it)->getPositionY() < -15)
	{
	  (*it)->setHealth(0);
	  return;
	}
    }
}

void Game::eraseBulletOut()
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if ((*it)->getPositionX() > XMAX ||
	   (*it)->getPositionY() > YMAX || 
	  (*it)->getPositionX() < -15 ||
	  (*it)->getPositionY() < -15)
	{
	  sendBulletErase(*it);
	  it = bulletList.erase(it);
	  it--;
	}
    }
}

void Game::eraseIaOut()
{
  for (std::list<IIa*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      if ((*it)->getPositionX() < -15)
	{
	  sendIaErase(*it);
	  it = iaList.erase(it);
	  it--;
	}
    }
}

void Game::eraseObsOut()
{
  for (std::list<MovingObstacle*>::iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      if ((*it)->getPositionX() < -15)
	{
	  sendObsErase(*it);
	  it = obsList.erase(it);
	  it--;
	}
    }
}

void Game::eraseBonusOut()
{
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      if ((*it)->getPositionX() < -15)
	{
	  sendBonusErase(*it);
	  it = bonusList.erase(it);
	  it--;
	}
    }
}


void Game::addPlayer(Player *p)
{
  mutexPlayers->MLock();
  playerList.push_back(p);
  mutexPlayers->MUnLock();
}

void Game::checkPlayer()
{
  mutexPlayers->MLock();
  if (humainList.size() < playerList.size())
    {
      if (playerList.back() == NULL)
	{
	  std::cout<<"fail"<<std::endl;
	  exit(0);
	}
      addHumainUnitByPlayer(playerList.back()->getId());
      }
  mutexPlayers->MUnLock();
}

bool Game::allDead()
{
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    if ((*it)->getHealth() > 0)
      return (false);
  return (true);
}

void Game::update(double time)
{
  // createRandomObs(time);
  // createRandomBonus(time);
  createRandomEnemie(time);
  for (std::list<IIa*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    (*it)->update(time);
  
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    (*it)->update(time);

  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    (*it)->update(time);
}

void Game::sendBulletErase(Bullet *b)
{
  Protocol::drawable * d = new Protocol::drawable(); 
 
  memset(d, 0, sizeof(Protocol::drawable));
  d->id = b->getId();
  d->xPosition = b->getPositionX();
  d->yPosition = b->getPositionY();
  d->type = b->getType();
  d->life = 0;
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
    (*it)->getSocketUdp()->sendv(sizeof(*d), d);
  mutexPlayers->MUnLock();
}

void Game::sendObsErase(MovingObstacle *b)
{
  Protocol::drawable * d = new Protocol::drawable(); 
  memset(d, 0, sizeof(Protocol::drawable));
  d->id = b->getId();
  d->xPosition = b->getPositionX();
  d->yPosition = b->getPositionY();
  d->type = Protocol::OBSTACLE;
  d->life = 0;
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
    (*it)->getSocketUdp()->sendv(sizeof( *d), d);
  mutexPlayers->MUnLock();
}

void Game::sendIaErase(IIa *b)
{
  Protocol::drawable * d = new Protocol::drawable(); 
  memset(d, 0, sizeof(Protocol::drawable));
  d->id = b->getId();
  d->xPosition = b->getPositionX();
  d->yPosition = b->getPositionY();
  d->type = b->getType();
  d->life = 0;
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
    (*it)->getSocketUdp()->sendv(sizeof(*d), d);
  mutexPlayers->MUnLock();
}

void Game::sendBonusErase(LifePowerUp *b)
{
  Protocol::drawable * d = new Protocol::drawable(); 
  memset(d, 0, sizeof(Protocol::drawable));
  d->id = b->getId();
  d->xPosition = b->getPositionX();
  d->yPosition = b->getPositionY();
  d->type = Protocol::BONUS;
  d->life = 0;
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
    (*it)->getSocketUdp()->sendv(sizeof(*d), d);
  mutexPlayers->MUnLock();
}

void Game::sendShipErase(HumainUnit *b)
{
  Protocol::drawable * d = new Protocol::drawable(); 
  memset(d, 0, sizeof(Protocol::drawable));
  d->id = b->getId();
  d->xPosition = b->getPositionX();
  d->yPosition = b->getPositionY();
  d->type = Protocol::SHIP;
  d->life = 0;
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
    (*it)->getSocketUdp()->sendv(sizeof(*d), d);
  mutexPlayers->MUnLock();
}

void Game::collision()
{
  for (std::list<IIa*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    if (collisionIaWithBullet((*it)) == true)
      {
	sendIaErase(*it);
	it = iaList.erase(it);
	it--;
      }
  
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    collisionHumainWithBullet((*it));
  
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    collisionWithEnemie((*it));

  // for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
  //   {
  //     if (collisionWithBullet((*it)) == true)
  // 	{
  // 	  sendBulletErase(*it);
  // 	  it = bulletList.erase(it);
  // 	  it--;
  // 	}
  //   }
  // for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
  //   if (collisionBWithObs((*it)) == true)
  //     {
  // 	sendBulletErase(*it);
  // 	it = bulletList.erase(it);
  // 	it--;
  //     }

  // for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
  //   collisionWithBonus((*it));
}

IIa* Game::createAIUnit(std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Protocol::patern_enemie patern)
{
  static int i = 0;
   IIa * u = iaFactory();
   u->init(i, pos, 2, h, w, t, this, patern);
   
   iaList.push_back(u);
   i++;
   return (u);
}

HumainUnit* Game::createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Player *p)
{
  static int i = 0;
  std::pair<float, float> pos(0, 0);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 10, 10);
  HumainUnit *h = new HumainUnit(speed, p->getId(), i, coll, health, strength, isDestroyable, this);

  humainList.push_back(h);
  i++;
  return (h);
}

MovingObstacle* Game::createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable)
{
  static int i = 0;
  MovingObstacle* l = new MovingObstacle(speed, i, coll, strength, isDestroyable);
 
  obsList.push_back(l);
  i++;
  return (l);
}

Player* Game::createPlayer(int id, std::string name, ISocket *tcp, ISocket *udp)
{
  Player* p = new Player(id, name, tcp, udp);

  mutexPlayers->MLock();
  playerList.push_back(p);
  mutexPlayers->MUnLock();

  return (p);
}

LifePowerUp* Game::createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, int strength)
{
  static int i = 0;
  LifePowerUp* l = new LifePowerUp(nb_life, i, coll, strength, isDestroyable);

  bonusList.push_back(l);
  i++;
  return (l);
}

Bullet *Game::createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_drawable type)
{
  static int i = 0;
  Bullet *b = new Bullet(idUnit, speed, i, rec, strength, isDestroyable, type);

  bulletList.push_back(b);
  i++;
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

// HumainUnit *Game::getUnitByPlayer(Player *p)const
// {
//     for (std::list<HumainUnit*>::const_iterator it = humainList.begin(); it != humainList.end(); it++)
//     {
//       if ((*it)->getPlayer() == p)
// 	return (*it);
//     }
//   return NULL;
// }
 
HumainUnit *Game::getUnitHumanByPlayer(int id)const
{
  mutexPlayers->MLock();
  for (std::list<HumainUnit*>::const_iterator it = humainList.begin(); it != humainList.end(); it++)
    {
      if ((*it)->getPlayerId() == id)
	{
	  mutexPlayers->MUnLock();
	  return (*it);
	}
    }
  mutexPlayers->MUnLock();
  return NULL;
}

IIa *Game::getUnitAI(int id)const
{
    for (std::list<IIa*>::const_iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

// Unit *Game::getUnit(int id)const
// {
//   Unit *u;

//   if ((u = getUnitHuman(id)) != NULL)
//     return (u);
//   else if ((u = getUnitAI(id)) != NULL)
//     return (u);
//   return (NULL);
// }

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
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  mutexPlayers->MUnLock();
	  return (*it);
	}
    }
  mutexPlayers->MUnLock();
  return NULL;
}

void Game::addPlayer(std::string name, ISocket *udp, ISocket *tcp)
{
  Player *p = createPlayer(playerList.size(), name, tcp, udp);

  createHumainUnit(humainList.size(), std::pair<float, float>(1, 1), 3, 1, true, p);
}

HumainUnit* Game::addHumainUnitByPlayer(int idPlayer)
{
  static int i = 0;

  std::pair<float, float> pos(50, 50);
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 35, 25);
 
  HumainUnit *h = new HumainUnit(std::pair<float, float> (1, 1), idPlayer, idPlayer, coll, 3, 1, true, this);
  
  humainList.push_back(h);
  i++;
  return (h);
}

int Game::getNbPlayer()const
{
  return (humainList.size());
}

Player *Game::getPlayerBySockTcp(ISocket *sock)const
{
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getSocketTcp() == sock)
	{
	  mutexPlayers->MUnLock();
	  return (*it);
	}
    }
  mutexPlayers->MUnLock();
  return (NULL);
}
 
Player *Game::getPlayerBySockUdp(ISocket *sock)const
{
  mutexPlayers->MLock();
  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end(); it++)
    {
      if ((*it)->getSocketUdp() == sock)
	{
	  mutexPlayers->MUnLock();
	  return (*it);
	}
    }
  mutexPlayers->MUnLock();
  return (NULL);
}

int Game::getId()const
{
  return (_id);
}

void Game::eraseBullet(int id)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end();)
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
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end();)
    {
      if ((*it)->getUnit() == idPlayer)
	bulletList.erase(it);
      it++;
    }
}

void Game::erasePlayer(int id)
{
  mutexPlayers->MLock();
  for (std::list<Player*>::iterator it = playerList.begin(); it != playerList.end();)
    {
      if ((*it)->getId() == id)
	{
	  playerList.erase(it);
	  mutexPlayers->MUnLock();
	  return;
	}
      else
	it++;
    }
  mutexPlayers->MUnLock();
}

void Game::eraseHumain(int id)
{
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end();)
    {
      if ((*it)->getPlayerId() == id)
	{
	  humainList.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Game::eraseIa(int id)
{
  for (std::list<IIa*>::iterator it = iaList.begin(); it != iaList.end();)
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
  for (std::list<MovingObstacle*>::iterator it = obsList.begin(); it != obsList.end();)
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
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end();)
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

void Game::eraseAllIa()
{
  while (!iaList.empty())
    iaList.pop_back();
}

void Game::eraseAllObs()
{
  while (!obsList.empty())
    obsList.pop_back();
}

void Game::eraseAllBonus()
{
  while (!bonusList.empty())
    bonusList.pop_back();
}

void Game::resetLife()
{
  for (std::list<HumainUnit*>::iterator it = humainList.begin(); it != humainList.end(); it++)
    (*it)->setHealth(3);
}

void Game::resetGame(double *time)
{
  *time = 0;
  eraseAllIa();
  eraseAllObs();
  eraseAllBonus();
  resetLife();
}

bool Game::isFriendlyBullet(Bullet *b)
{
  if (b->getUnit() == 0)
    return (true);
  return (false);
}

bool Game::collisionWithBullet(Bullet *u)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
      if (u != (*it) && ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth())))
	{
	  sendBulletErase(*it);
	  bulletList.erase(it);
	  return (true);
	}
    }
  return (false);	
}

bool Game::collisionHumainWithBullet(HumainUnit *u)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if (isFriendlyBullet(*it) == true)
      	return (false);
      float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
     if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  u->setHealth(u->getHealth() - 1);
	  sendBulletErase(*it);
	  bulletList.erase(it);
	  return (true);
	}
    }
  return (false);	
}

bool Game::collisionIaWithBullet(IIa *u)
{
  for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      if (isFriendlyBullet(*it) != true)
       	return (false);
      float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	   sendBulletErase(*it);
	  bulletList.erase(it);
	  return (true);
	}
    }
  return (false);	
}

bool Game::collisionWithEnemie(HumainUnit *u)
{
  for (std::list<IIa*>::iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  u->setHealth(0);
	  sendIaErase(*it);
	  iaList.erase(it);
	  return (true);
	}
    }
  return (false);
}

bool Game::collisionUWithObs(Unit *u)
{
  for (std::list<MovingObstacle*>::iterator it = obsList.begin(); it != obsList.end(); it++)
    {
       float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
     
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
 	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	return (true);
    }
  return (false);
}

bool Game::collisionBWithObs(Bullet *b)
{
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      float y = b->getPositionY() - (b->getHeight() / 2);
      float x = b->getPositionX() - (b->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
     
       if ((y + b->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + b->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  sendBonusErase(*it);
	  bonusList.erase(it);
	  return (true);
	}
    }
  return (false);
}

bool Game::collisionWithBonus(HumainUnit *u)
{
  for (std::list<LifePowerUp*>::iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      float y = u->getPositionY() - (u->getHeight() / 2);
      float x = u->getPositionX() - (u->getWidth() / 2);
      float obsY = (*it)->getPositionY() - ((*it)->getHeight() / 2); ;
      float obsX = (*it)->getPositionX() - ((*it)->getWidth() / 2); ;;
     
      if ((y + u->getHeight() > obsY
	   && y < obsY + (*it)->getHeight()) &&
	  (x + u->getWidth() > obsX &&
	   x < obsX + (*it)->getWidth()))
	{
	  if (u->getHealth() < 3)
	    (*it)->applyToUnit(u);
	  sendBonusErase(*it);
	  bonusList.erase(it);
	  return true;
	}
    }
  return (false);
}

void Game::fire(int id)
{
  HumainUnit *u = getUnitHumanByPlayer(id);
  
  if (u == NULL)
    return;
  double time  = u->getTimeBullet();
  if (t - time < 1)
      return;
  std::pair<float, float> pos = u->getPosition();
  ICollisionDefinition *coll = new RectangleCollisionDefinition(pos, 30, 10);
  
  createBullet(0, std::pair<float, float>(1, 1), bulletList.size(), coll, 1, true, Protocol::BULLET_LINEAR);
  u->setTimeBullet(t);
}

// void Game::fire_ia(int id)
// {
//   IIa *u = getUnitAI(id);
  
//   if (u == NULL)
//     return;
  
//   ICollisionDefinition *coll;

//   if (u->getType() == Protocol::ENEMY_EASY)
//      {
//        coll = new RectangleCollisionDefinition(u->getPosition(), 1, 1);
//        createBullet(1, std::pair<float, float>(-1, -1), bulletList.size(), coll, 1, true,  Protocol::BULLET_LINEAR);
//      }    
//   else if (u->getType() == Protocol::ENEMY_HARD)
//      {
//        coll = new RectangleCollisionDefinition(u->getPosition(), 50, 1);
//        createBullet(1, std::pair<float, float>(-1, -1), bulletList.size(), coll, 1, true, Protocol::BULLET_RAYON);
//      }
// }

void Game::move(int id, Protocol::move *m)
{
   Unit *u = getUnitHumanByPlayer(id);
  
  if (u == NULL)
    return;
  //  if (collisionUWithObs(u) == false)
  u->getDefinition()->move(m, 2);
}
// void Game::moveIa(int id, Protocol::move *m)
// {
//   //std::cout<<"move : id : "<<id<<std::endl;
//   Unit *u = getUnitAI(id);
  
//   if (u == NULL)
//     return;
//   //  if (collisionUWithObs(u) == false)
//   u->getDefinition()->move(m, 2);
// }

int Game::getIaSize()const
{
  return (iaList.size());
}

int Game::getHumainSize()const
{
  return (humainList.size());
}

int Game::getBulletSize()const
{
  return (bulletList.size());
}

int Game::getObsSize()const
{
  return (obsList.size());
}

int Game::getBonusSize()const
{
  return (bonusList.size());
}

void Game::createRandomObs(double time)
{
  std::pair<float, float> newSpeed(1,1);
  float x = XMAX + 1;
  float y;
  //srand(time);
  y = rand() %  YMAX + 1;
  std::pair<float,float> pos(x,y);
  int strength = rand() % 3 + 1;
  int Des = rand() % 2;
  bool Destroy = true;
  if (Des == 0)
    Destroy = false;
  
  ICollisionDefinition *Col = new RectangleCollisionDefinition(pos, 2, 2);
  if (time >= 10 && time <= 50)
    {
      if ((int)time % 5 == 0)
		createLinearMovingObstacle((this->obsList.size() + 1), newSpeed, Col, strength, Destroy);
    }
  else if (time > 50 && time <= 90)
    {
      if ((int)time % 3 == 0)
		createLinearMovingObstacle((this->obsList.size() + 1), newSpeed, Col, strength, Destroy);
    }
  else if (time > 90)
    {
      if ((int)time % 2 == 0)
		createLinearMovingObstacle((this->obsList.size() + 1), newSpeed, Col, strength, Destroy);
    }
}

void Game::createRandomBonus(double time)
{
  if ((int)time % 15 == 0)
    {	
      float x = rand() % XMAX + 1;
      float y;
      y = rand() % YMAX + 1;
      std::pair<float,float> pos(x, y);
      int life = rand() % 3 + 1;
      ICollisionDefinition *Col = new RectangleCollisionDefinition(pos, 1, 1);
      createBonus(life, this->bonusList.size(), Col, false, 0);
    }
}
void Game::CreateEnemiePack(Protocol::type_drawable type, int patern, int speed, int strength, int life)
{
  float x = XMAX + 1;
  float y = rand() % (YMAX - 15) + 5;
  std::pair<float, float> pos(x,y);
  std::pair<float, float> pos1(x, y - 1);
  std::pair<float, float> pos2(x, y + 1);
  
createAIUnit(pos, speed, 28, 36, type,  Protocol::PACKV);
createAIUnit(pos1, speed, 28, 36, type,  Protocol::PACKV);
createAIUnit(pos2, speed, 28, 36, type,  Protocol::PACKV);
}

void Game::CreateEnemiePaternSolo(Protocol::type_drawable type, int patern,int speed, int strength, int life)
{
  
  float x = XMAX + 1;
  float y = rand() % YMAX + 1;
  std::pair<float, float> pos(x, y);
  
  createAIUnit(pos, speed, 35, 25, type,  Protocol::SOLO);
}

// void Game::CreateEnemiePaternLine(Protocol::type_drawable type, int patern, std::pair<float,float> newSpeed, int strength, int life)
// {
// 		float x = XMAX + 1;
// 		float y = rand() % YMAX + 1;
// 		int i;
// 		std::pair<float, float> pos(x,y);
// 		Protocol::patern_enemie pat;

// 		if (patern == 4)
// 			pat = Protocol::LINEUP;
// 		else if (patern == 5)
// 			pat = Protocol::LINEDOWN;
// 		else
// 			pat = Protocol::LINE;

// 		for (i = 0; i < 4; i++)
// 		{
// 			std::pair<float, float> pos(x - (2 * i), y);
// 			ICollisionDefinition *Col = new RectangleCollisionDefinition(pos, 1, 2);
// 			createAIUnit(this->iaList.size() + 1,newSpeed, Col, life, strength, 
// 							true, type, pat);
// 		}
// }

// void Game::CreateEnemiePaternVFLY(Protocol::type_drawable type, int patern,std::pair<float,float> newSpeed, int strenght, int life)
// {
// }

void Game::createRandomEnemie(double time)
{
  if (iaList.size() < 8)
    {
      static long verif = 0;
      if (time > 3)
	{
	  if ((int)time % 3 || verif == time)
	    return;
	  verif = time;
      // int difficult;
      // int patern;
      // int life;
      // int strength;
      // int newSpeed;
      // Protocol::type_drawable type;
      // Protocol::patern_enemie pat;
  
      // difficult = rand() % 2;
      // patern = rand() % 2;

      // if (difficult == 0)
      // 	type = Protocol::ENEMY_EASY;
      // else
      // 	type = Protocol::ENEMY_HARD;

      // if (type == 1)
      // 	{
      // 	  newSpeed = 3;
      // 	  life = 1;
      // 	  strength = 1;
      // 	}
      // else
      // 	{
      // 	  newSpeed = 4;
      // 	  life = 2;
      // 	  strength = 2;
      // 	}

      // if (patern < 2)
	CreateEnemiePaternSolo(Protocol::ENEMY_EASY, 0, 3, 0, 1);
      // CreateEnemiePaternSolo(type,patern, newSpeed, strength, life);
      // else if (patern == 2)
      // 	CreateEnemiePack(type, patern, newSpeed, strength, life);
      // else if (patern >= 4)
      // 	CreateEnemiePaternLine(type, patern, newSpeed, strength, life);
      
      // else
      // 	CreateEnemiePaternVFLY(type, patern, newSpeed, strength, life);
      // }
	}
    }
}


void Game::sendGame()const
{
  sendBullet();
  //sendObs();
  sendIA();
  //sendBonus();
  sendShip();
}

void Game::sendBullet()const
{
  for (std::list<Bullet*>::const_iterator it = bulletList.begin(); it != bulletList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      memset(d, 0, sizeof(Protocol::drawable));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->yPosition = (*it)->getPositionY();
      d->type = (*it)->getType();
      d->life = 1;
      mutexPlayers->MLock();
      for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
	(*it)->getSocketUdp()->sendv(sizeof(*d), d);
      mutexPlayers->MUnLock();
    }
}

void Game::sendObs()const
{
  for (std::list<MovingObstacle*>::const_iterator it = obsList.begin(); it != obsList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      memset(d, 0, sizeof(Protocol::drawable));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->yPosition = (*it)->getPositionY();
      d->type = Protocol::OBSTACLE;
      d->life = 1;
      mutexPlayers->MLock();
      for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
	(*it)->getSocketUdp()->sendv(sizeof( *d), d);
      mutexPlayers->MUnLock();
    }
}

void Game::sendIA()const
{
  for (std::list<IIa*>::const_iterator it = iaList.begin(); it != iaList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      memset(d, 0, sizeof(Protocol::drawable));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->yPosition = (*it)->getPositionY();
      d->type = (*it)->getType();
      d->life = 1;
      mutexPlayers->MLock();
      for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
	(*it)->getSocketUdp()->sendv(sizeof(*d), d);
      mutexPlayers->MUnLock();
    }
}

void Game::sendBonus()const
{
  for (std::list<LifePowerUp*>::const_iterator it = bonusList.begin(); it != bonusList.end(); it++)
    {
      Protocol::drawable * d = new Protocol::drawable(); 
      memset(d, 0, sizeof(Protocol::drawable));
      d->id = (*it)->getId();
      d->xPosition = (*it)->getPositionX();
      d->yPosition = (*it)->getPositionY();
      d->type = Protocol::BONUS;
      d->life = 1;
      mutexPlayers->MLock();
      for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
	(*it)->getSocketUdp()->sendv(sizeof(*d), d);
      mutexPlayers->MUnLock();
    }
}

void Game::sendShip()const
{
  for (std::list<HumainUnit*>::const_iterator it = humainList.begin(); it != humainList.end(); it++)
    {      
      if ((*it)->getHealth() > 0)
	{
	  Protocol::drawable * d = new Protocol::drawable(); 
	  memset(d, 0, sizeof(Protocol::drawable));
	  d->id = (*it)->getId();
	  d->xPosition = (*it)->getPositionX();
	  d->yPosition = (*it)->getPositionY();
	  d->type = Protocol::SHIP;
	  d->life = (*it)->getHealth();
	  mutexPlayers->MLock();
	  for (std::list<Player*>::const_iterator it = playerList.begin(); it != playerList.end();it++)
	    (*it)->getSocketUdp()->sendv(sizeof(*d), d);
	  mutexPlayers->MUnLock();
	}
    }
}
