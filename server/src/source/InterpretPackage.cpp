//
// InterpretPackage.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server/src
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Wed Jan  9 10:54:24 2013 marche_m (Maxime Marchès)
// Last update Fri Jan 11 18:54:32 2013 mathieu leurquin
//

#include "../include/InterpretPackage.hpp"

InterpretPackage::InterpretPackage(Server *s)
{
  _funcMap[Protocol::REGISTER] = &InterpretPackage::execRegister;
  _funcMap[Protocol::LOGIN] = &InterpretPackage::execLogin;
  _funcMap[Protocol::GET_GAME_LIST] = &InterpretPackage::execGetGameList;
  _funcMap[Protocol::GAME_LIST] = &InterpretPackage::execGameList;
  _funcMap[Protocol::JOIN_GAME] = &InterpretPackage::execJoinGame;
  _funcMap[Protocol::CREATE_GAME] = &InterpretPackage::execCreateGame;
  _funcMap[Protocol::SEND_WORLD] = &InterpretPackage::execSendWorld;
  _funcMap[Protocol::MOVE] = &InterpretPackage::execMove;
  _funcMap[Protocol::FIRE] = &InterpretPackage::execFire;
  _funcMap[Protocol::RESPONSE] = &InterpretPackage::execResponse;
  _server = s;
}

void	InterpretPackage::executeCmd(void * header, void * data, ISocket * sock)
{
  std::cout << "executeCmd" << std::endl;
  int hdTmp[2];

  memcpy(hdTmp, header, 2 * sizeof(int));
  std::cout << "id:" << hdTmp[0] << std::endl;
  std::cout << "size:" << hdTmp[1] << std::endl;
  void (InterpretPackage::*pMethod)(void *, ISocket *) = (this->_funcMap[((Protocol::type_cmd)hdTmp[0])]);
  (this->*pMethod)(data, sock);
}

void	InterpretPackage::execRegister(void * data, ISocket * sock)
{

}

void	InterpretPackage::execLogin(void * data, ISocket * sock)
{
  std::cout << "execLogin" << std::endl;
  Protocol::login * dataTmp = new Protocol::login();
  memset(dataTmp, 0, sizeof(*dataTmp));
  memcpy(dataTmp, data, sizeof(*dataTmp));
  std::cout << dataTmp->login << std::endl;
  std::cout << dataTmp->passwd << std::endl;
}

void	InterpretPackage::execGetGameList(void * data, ISocket * sock)
{
  
}

void	InterpretPackage::execGameList(void * data, ISocket * sock)
{

}

void	InterpretPackage::execJoinGame(void * data, ISocket * sock)
{

}

void	InterpretPackage::execCreateGame(void * data, ISocket * sock)
{

}

void	InterpretPackage::execSendWorld(void * data, ISocket * sock)
{
  std::cout << "exexSendWorld" << std::endl;
  std::list <Game*> listGameCpy = _server->getGameList();
  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      (*it)->formatGameSend();
      //send
    }
}

void	InterpretPackage::execMove(void * data, ISocket * sock)
{
  Player *p;
  std::list <Game*> listGameCpy = _server->getGameList();

  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      if ((p = (*it)->getPlayerBySockUdp(sock)) != NULL)
	(*it)->move(p->getId());
    }
}

void	InterpretPackage::execFire(void * data, ISocket * sock)
{
  Player *p;
  std::list <Game*> listGameCpy = _server->getGameList();
  
  for (std::list<Game*>::iterator it = listGameCpy.begin(); it != listGameCpy.end(); it++)
    {
      if ((p = (*it)->getPlayerBySockUdp(sock)) != NULL)
	(*it)->move(p->getId());
    }
  
}

void	InterpretPackage::execResponse(void * data, ISocket * sock)
{

}