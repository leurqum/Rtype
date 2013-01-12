#ifndef __GAME__
#define __GAME__

#include <list>
#include <map>
#include "Player.hpp"
#include "RectangleCollisionDefinition.hpp"
#include "./../../Abs_Socket/ISocket.hpp"
#include "./../../../protocol.h"
#include "MovingObstacle.hpp"
#include "BasicWeapon.hpp"
#include "Bullet.hpp"
#include "LifePowerUp.hpp"
#include <iostream>
#include <string.h>

class IAUnit;
class HumainUnit;
class Game
{
private:
  int _id;
  std::list<IAUnit*>		iaList;
  std::list<HumainUnit*>	humanList;
  std::list<Player*>		playerList;
  std::list<Bullet*>		bulletList;
  std::list<MovingObstacle*>	obsList;
  std::list<LifePowerUp*>	bonusList;
public:
  Game(int id);
  void loop();
  void update();
  void collision();
  IAUnit* createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable);
  HumainUnit* createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Player *p);
  MovingObstacle* createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable);
  Player* createPlayer(int id, std::string name, int life, ISocket *socket_tcp, ISocket *socket_udp);
  LifePowerUp* createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, int strength);
  Bullet *createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable);
  Bullet *getBullet(int id)const;
  HumainUnit *getUnitByPlayer(Player *p)const;
  HumainUnit *getUnitHuman(int id)const;
  IAUnit *getUnitAI(int id)const;
  Unit *getUnit(int id)const;
  MovingObstacle *getObs(int id)const;
  LifePowerUp *getLifePowerUp(int id)const;
  Player *getPlayer(int id)const;
  void addPlayer(std::string, ISocket *, ISocket *);
  int getNbPlayer()const;
  Player *getPlayerBySockTcp(ISocket *socket_tcp)const;
  Player *getPlayerBySockUdp(ISocket *socket_udp)const;
  int getId()const;
  void eraseBullet(int id);
  void eraseBulletsPlayer(int idPlayer);
  void erasePlayer(int id);
  void eraseHumain(int id);
  void eraseIa(int id);
  void eraseObs(int id);
  void eraseBonus(int id);
  
  bool isFriendlyBullet(Bullet *b);
  bool collisionIaWithBullet(IAUnit *u);
  bool collisionHumainWithBullet(HumainUnit *u);
  bool collisionWithEnemie(HumainUnit *u);
  bool collisionUWithObs(Unit *u);
  bool collisionBWithObs(Bullet *b);
  bool collisionWithBonus(HumainUnit *u);

  void fire(int id);
  void move(int id);

  int getSizeGame()const;
  void *formatGameSend();
};

#endif //__GAME__

#include "IAUnit.hpp"
#include "HumainUnit.hpp"
