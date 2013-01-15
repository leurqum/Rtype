#ifndef __PLAYER__
#define __PLAYER__

#include <string>
#include "./../../Abs_Socket/ISocket.hpp"

class Player
{
private:
  int		_id;
  std::string	_name;
  ISocket *	_socket_tcp;
  ISocket *	_socket_udp;
public:
  Player(int id, std::string name, ISocket *socket_tcp, ISocket *socket_udp);
  ~Player(void);
  int getId()const;
  std::string getName()const;
  ISocket *getSocketUdp()const;
  ISocket *getSocketTcp()const;
};

#endif
