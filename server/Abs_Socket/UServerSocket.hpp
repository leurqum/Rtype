//
// UServerSocket.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:46 2013 marche_m (Maxime Marchès)
// Last update Wed Jan 16 13:54:11 2013 mathieu leurquin
//

#ifndef __U_SERVER_SOCKET__
# define __U_SERVER_SOCKET__

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <sstream>

#include "IServerSocket.hpp"
#include "USocket.hpp"
#include "../src/include/InterpretPackage.hpp"

class UServerSocket : public IServerSocket
{
public:
  UServerSocket(Server *s);
  virtual	~UServerSocket();
  bool		init(std::string const & listenHost, std::string const & listenPort);
  ISocket	* myaccept(void * sockType);
  void		launch();

private:
  void		addNewPeer(void * sock);
  int		getSocketTcp() { return _listenSocketTcp; }
  int		selectSockets();
  void		callBack(std::list<int>::iterator & it);

  int				_listenSocketTcp;
  int				_listenSocketUdp;
  std::list<int>		_clientsList;
  std::map<int, ISocket *>	_clientsSocksMap;
  std::map<std::string, ISocket *>	_clientsSocksUdpMap;
  fd_set			_readFd;
  InterpretPackage*		_interPckg;
  struct sockaddr_in		_servAddr;
  Server			* _server;
  int							_portUdpPeer;
};

#endif

