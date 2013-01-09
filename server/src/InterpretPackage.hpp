//
// InterpretPackage.hpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server/src
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Wed Jan  9 10:54:26 2013 marche_m (Maxime Marchès)
// Last update Wed Jan  9 11:15:43 2013 marche_m (Maxime Marchès)
//

#ifndef __INTERPRET_PACKAGE__
# define __INTERPRET_PACKAGE__

#include <map>
#include "./../../protocol.h"
#include "./../Abs_Socket/ISocket.hpp"

class InterpretPackage
{
public:
  InterpretPackage();
  void exectuteCmd(void * header, void * data, ISocket * sock);

private:
  void execRegister(void * data, ISocket * sock);
  void execLogin(void * data, ISocket * sock);
  void execGetGameList(void * data, ISocket * sock);
  void execGameList(void * data, ISocket * sock);
  void execJoinGame(void * data, ISocket * sock);
  void execCreateGame(void * data, ISocket * sock);
  void execSendWorld(void * data, ISocket * sock);
  void execMove(void * data, ISocket * sock);
  void execFire(void * data, ISocket * sock);
  void execResponse(void * data, ISocket * sock);

  std::map<Protocol::type_cmd, void (InterpretPackage::*)(void *, ISocket *)>	_funcMap;
};

#endif
