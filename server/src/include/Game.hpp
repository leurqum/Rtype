#ifndef __GAME__
#define __GAME__

#include <list>
#include <map>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "./../../Abs_Socket/ISocket.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "../../Abs_Thread_mutex/portaThread.hpp"
#include "RectangleCollisionDefinition.hpp"
#include "./../../../protocol.h"
#include "MovingObstacle.hpp"
#include "LifePowerUp.hpp"

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


class IIa;
class HumainUnit;

typedef IIa *(*maker_Ia)();

class MyTimer
{
public:
  MyTimer()
  {
    this->reset();
  }
  long getDiff()
  {
    struct timeval now;
    long seconds;
    long useconds;
    long mtime;

    gettimeofday(&now, NULL);
    seconds  = now.tv_sec  - _start.tv_sec;
    useconds = now.tv_usec - _start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    return mtime;
  }
  void reset()
  {
    gettimeofday(&_start, NULL);
  }

private:
  struct timeval _start;
};

class Game
{

public:
  MyTimer			timer;
  long t;
  maker_Ia			iaFactory;
  std::list<Player*>		playerList;
  int _id;
  std::list<IIa*>		iaList;
  std::list<HumainUnit*>	humainList;

  MyMutex *mutexPlayers;
 


  std::list<Bullet*>		bulletList;
  std::list<MovingObstacle*>	obsList;
  std::list<LifePowerUp*>	bonusList;
public:
  Game(int id);
  void checkPlayer();
  void loop();
  void update(double time);
  void collision();
  IIa* createAIUnit(std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Protocol::patern_enemie patern);
  HumainUnit* createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Player *p);
  MovingObstacle* createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable);
  Player* createPlayer(int id, std::string name, ISocket *socket_tcp, ISocket *socket_udp);
  LifePowerUp* createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, int strength);
  Bullet *createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable, Protocol::type_drawable);
 
  void eraseIaOut();
  void eraseBulletOut();
  void eraseBonusOut();
  void eraseObsOut();

  void addPlayer(Player *p);
  Bullet *getBullet(int id)const;
  HumainUnit *getUnitHumanByPlayer(int id)const;
  HumainUnit* addHumainUnitByPlayer(int id);
  //void moveIa(int id, Protocol::move *m);
  IIa *getUnitAI(int id)const;
  MovingObstacle *getObs(int id)const;
  LifePowerUp *getLifePowerUp(int id)const;
  Player *getPlayer(int id)const;
  void addPlayer(std::string, ISocket *, ISocket *);
  int getNbPlayer()const;
  Player *getPlayerBySockTcp(ISocket *socket_tcp)const;
  Player *getPlayerBySockUdp(ISocket *socket_udp)const;
  int getId()const;

  void sendBulletErase(Bullet *b);
  void sendObsErase(MovingObstacle *b);
  void sendIaErase(IIa *b);
  void sendBonusErase(LifePowerUp *b);
  void sendShipErase(HumainUnit *b);


  void eraseBullet(int id);
  void eraseBulletsPlayer(int idPlayer);
  void erasePlayer(int id);
  void eraseHumain(int id);
  void eraseIa(int id);
  void eraseObs(int id);
  void eraseBonus(int id);
  
  void eraseAllIa();
  void eraseAllObs();
  void eraseAllBonus();
  void resetLife();
  void resetGame(double *time);
  bool allDead();

  bool isFriendlyBullet(Bullet *b);
  bool collisionWithBullet(Bullet *u);
  bool collisionIaWithBullet(IIa *u);
  bool collisionHumainWithBullet(HumainUnit *u);
  bool collisionWithEnemie(HumainUnit *u);
  bool collisionUWithObs(Unit *u);
  bool collisionBWithObs(Bullet *b);
  bool collisionWithBonus(HumainUnit *u);

  //void fire_ia(int id);
  void fire(int id);
  void move(int id, Protocol::move *m);

  void createRandomObs(double time);
  void createRandomBonus(double time);
  void createRandomEnemie(double time);
  void CreateEnemiePaternVFLY(Protocol::type_drawable type, int,std::pair<float,float> newSpeed, int, int);
  void CreateEnemiePaternLine(Protocol::type_drawable type, int,std::pair<float,float> newSpeed, int, int);
  void CreateEnemiePaternSolo(Protocol::type_drawable type, int,int newSpeed, int, int);
  void CreateEnemiePack(Protocol::type_drawable type, int, int, int, int);

  int getIaSize()const;
  int getHumainSize()const;
  int getBulletSize()const;
  int getObsSize()const;
  int getBonusSize()const;

  void sendGame()const;
  void sendBullet()const;
  void sendObs()const;
  void sendIA()const;
  void sendBonus()const;
  void sendShip()const;
};

#include "IIA.hpp"
#include "HumainUnit.hpp"

#endif //__GAME__
