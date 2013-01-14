#ifndef __SERVER__
#define __SERVER__

#include "Player.hpp"
#include "Game.hpp"

class UServerSocket;
class Server
{
private:
  std::list<Player *>	playerListWaiting;
  std::list<Game *>	gameList;
  UServerSocket *	server_socket;
public:
  Server();
  
  int getNbGame()const;
  
  Player *getPlayerWaiting(int id)const;
  Game *getGame(int id)const;
  std::list<Game*> &getGameList();

  void erasePlayerWaiting(int id);
  void eraseGame(int id);
  
  Player* createPlayerWaiting(int id, std::string name, int life, ISocket *socket_tcp, ISocket *socket_upd);
  Game *createGame(int id);
};

#endif

#include "../../Abs_Socket/UServerSocket.hpp"
