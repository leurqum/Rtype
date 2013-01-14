//
// InterpretPackage.hpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server/src
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Wed Jan  9 10:54:26 2013 marche_m (Maxime Marchès)
// Last update Mon Jan 14 10:33:19 2013 marche_m (Maxime Marchès)
//

#ifndef __INTERPRET_PACKAGE__
# define __INTERPRET_PACKAGE__

#include <map>
#include <iostream>
#include <string.h>
#include "./../../../protocol.h"
#include "./../../Abs_Socket/ISocket.hpp"

class Server;
class InterpretPackage
{
public:
  InterpretPackage(Server *s);
  void executeCmd(void * header, void * data, ISocket * sock);	//Max
  
private:
  void execRegister(void * data, ISocket * sock);	//Max
  void execLogin(void * data, ISocket * sock);		//Max
  void execGetGameList(void * data, ISocket * sock);	//Matthieu
  void execGameList(void * data, ISocket * sock);	//Matthieu
  void execJoinGame(void * data, ISocket * sock);	//Max
  void execCreateGame(void * data, ISocket * sock);	//Max
  void execSendWorld(void * data, ISocket * sock);	//Matthieu
  void execMove(void * data, ISocket * sock);		//Matthieu
  void execFire(void * data, ISocket * sock);		//Matthieu
  void execResponse(void * data, ISocket * sock);	//Max

  std::map<Protocol::type_cmd, void (InterpretPackage::*)(void *, ISocket *)>	_funcMap;
private:
  Server *_server;
};

#endif

#include "Server.hpp"
