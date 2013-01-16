//
// Server.cpp for  in /home/leurqu_m//Documents/tek3/rtype/Rtype/server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Fri Jan 11 10:59:06 2013 mathieu leurquin
// Last update Wed Jan 16 10:22:41 2013 mathieu leurquin
//

#include "../include/Server.hpp"

#ifdef __unix__
	#include <unistd.h>
#endif
#ifdef _WIN32
	#include <Windows.h>
#endif

Server::Server()
{
  server_socket = new MyServerSocket(this);
  this->createGame(0);
  if (server_socket->init("", "4242") == true)
    server_socket->launch();
}

Player *Server::getPlayerWaiting(int id)const
{
  for (std::list<Player*>::const_iterator it = playerListWaiting.begin(); it != playerListWaiting.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

std::list<Game*> &Server::getGameList()
{
  return (this->gameList);
}
 
Game *Server::getGame(int id)const
{
  for (std::list<Game*>::const_iterator it = gameList.begin(); it != gameList.end(); it++)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}  
 
void Server::erasePlayerWaiting(int id)
{
  for (std::list<Player*>::iterator it = playerListWaiting.begin(); it != playerListWaiting.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  playerListWaiting.remove(*it);
	  return;
	}
    }
}

void Server::eraseGame(int id)
{
  for (std::list<Game*>::iterator it = gameList.begin(); it != gameList.end(); it++)
    {
      if ((*it)->getId() == id)
	gameList.erase(it);
      else
	it++;
    }
}  
 
Player* Server::createPlayerWaiting(int id, std::string name, ISocket *socket_tcp, ISocket *socket_udp)
{
  Player* p = new Player(id, name, socket_tcp, socket_udp);

  playerListWaiting.push_back(p);

  //TEST
  
  Protocol::join_game *game = new Protocol::join_game();
  game->id = 0;
  
  (*(gameList.begin()))->addPlayer(p);

  std::cout<<p->getId()<<std::endl;
  this->erasePlayerWaiting(p->getId());

  
  return (p);
}

int Server::getNbGame()const
{
  return (gameList.size());
}

#ifdef __unix__

void	*callHandle(void * data)
{
  Server * s = static_cast<Server *>(data);
  s->launchGame(s->gameList.size());

  return 0;
}

#endif
#ifdef _WIN32

DWORD WINAPI callHandle(LPVOID data)
{
  Server * s = static_cast<Server *>(data);
  s->launchGame(s->gameList.size());

  return 0;
}

#endif

void Server::createGame(int id)
{ 
  
  MyThread *th;
  
#ifdef __unix__
  th = new MyThread(NULL, callHandle, 0, this);
#endif
#ifdef _WIN32
 // th = new MyThread(NULL, (LPTHREAD_START_ROUTINE)(ptr)g, NULL);
#endif
  threadList.push_back(th);
  th->THStart();
}

void Server::launchGame(int id)
{
  Game *g = new Game(id);
  
  std::cout<<"new game"<<std::endl;
  gameList.push_back(g);
  g->loop();
}
