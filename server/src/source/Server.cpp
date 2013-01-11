//
// Server.cpp for  in /home/leurqu_m//Documents/tek3/rtype/Rtype/server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Fri Jan 11 10:59:06 2013 mathieu leurquin
// Last update Fri Jan 11 19:31:01 2013 mathieu leurquin
//

#include "../include/Server.hpp"

Server::Server()
{
  server_socket = new UServerSocket(this);
  //sock->setUDP(true); //Problem avec l'udp ...
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
	playerListWaiting.erase(it);
      else
	it++;
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
 
Player* Server::createPlayerWaiting(int id, std::string name, int life, ISocket *socket_tcp, ISocket *socket_udp)
{
  Player* p = new Player(id, name, life, socket_tcp, socket_udp);

  playerListWaiting.push_back(p);
  return (p);
}

Game *Server::createGame(int id)
{
  Game *g = new Game();

  gameList.push_back(g);
  return (g);
}
