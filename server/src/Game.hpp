#ifndef __GAME__
#define __GAME__

#include <list>
#include <map>
#include "IAUnit.hpp"
#include "HumainUnit.hpp"
#include "Player.hpp"
#include "MovingObstacle.hpp"
#include "LifePowerUp.hpp"
#include "BasicWeapon.hpp"
#include "Bullet.hpp"
#include "RectangleCollisionDefinition.hpp"

class CommandManager;
class Game
{
public:
    std::map<int, void (Game::*)(int id)> _fcts;
private:
  CommandManager *_cmd;
  std::list<IAUnit*>		iaList;
  std::list<HumainUnit*>	humanList;
  std::list<Player*>		playerList;
  std::list<Bullet*>		bulletList;
  std::list<MovingObstacle*>	obsList;
  std::list<LifePowerUp*>	bonusList;
public:
  Game();
  void loop();

  IAUnit* createAIUnit(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int health, int strength, bool isDestroyable, Game *game);
  HumainUnit* createHumainUnit(int id, std::pair<float, float> speed, int health, int strength, bool isDestroyable, Game *game, Player *p);
  MovingObstacle* createLinearMovingObstacle(int id, std::pair<float, float> speed, ICollisionDefinition *coll, int strength, bool isDestroyable, Game *game);
  Player* createPlayer(int id, std::string name, int life);
  LifePowerUp* createBonus(int nb_life, int id, ICollisionDefinition *coll, bool isDestroyable, Game *game, int strength);
  Bullet *createBullet(int idUnit, std::pair<float, float> speed, int id, ICollisionDefinition *rec, int strength, bool isDestroyable);
  Bullet *getBullet(int id)const;
  HumainUnit *getUnitByPlayer(Player *p)const;
  HumainUnit *getUnitHuman(int id)const;
  IAUnit *getUnitAI(int id)const;
  Unit *getUnit(int id)const;
  MovingObstacle *getObs(int id)const;
  LifePowerUp *getLifePowerUp(int id)const;
  Player *getPlayer(int id)const;
  void addPlayer(std::string);
  int getNbPlayer()const;

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
};

#endif //__GAME__

#include "CommandManager.hpp"
