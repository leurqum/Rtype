#ifndef __SERVER__
#define __SERVER__

#include "Player.hpp"
#include "Game.hpp"

class Server
{
private:
  std::list<Player *> playerListWaiting;
  std::list<Game *> gameList;
public:
  Player *getPlayerWaiting(int id)const;
  Game *getGame(int id)const;
  
  void erasePlayerWaiting(int id);
  void eraseGame(int id);
  
  Player* createPlayerWaiting(int id, std::string name, int life, ISocket *socket_tcp, ISocket *socket_upd);
  Game *createGame(int id);
};

#endif
