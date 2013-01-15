#ifndef __SERVER__
#define __SERVER__

#include "Player.hpp"
#include "Game.hpp"

#include "../../Abs_Socket/portaSocket.hpp"
#include "../../Abs_Thread_mutex/portaThread.hpp"

class Server
{
private:
  std::list<Player *>	playerListWaiting;
  std::list<Game *>	gameList;
  std::list<MyThread*>	threadList;
  MyServerSocket*	server_socket;
public:
  Server();
  
  int getNbGame()const;
  
  Player *getPlayerWaiting(int id)const;
  Game *getGame(int id)const;
  std::list<Game*> &getGameList();

  void erasePlayerWaiting(int id);
  void eraseGame(int id);
  
  Player* createPlayerWaiting(int id, std::string name, ISocket *socket_tcp, ISocket *socket_upd);
  void createGame(int id);
};

#endif
