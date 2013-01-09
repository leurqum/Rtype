//
// InterpretPackage.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server/src
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Wed Jan  9 10:54:24 2013 marche_m (Maxime Marchès)
// Last update Wed Jan  9 16:32:43 2013 marche_m (Maxime Marchès)
//

#include "../include/InterpretPackage.hpp"

InterpretPackage::InterpretPackage()
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
}

void	InterpretPackage::exectuteCmd(void * header, void * data, ISocket * sock)
{

}

void	InterpretPackage::execRegister(void * data, ISocket * sock)
{

}

void	InterpretPackage::execLogin(void * data, ISocket * sock)
{

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

}

void	InterpretPackage::execMove(void * data, ISocket * sock)
{

}

void	InterpretPackage::execFire(void * data, ISocket * sock)
{

}

void	InterpretPackage::execResponse(void * data, ISocket * sock)
{

}


