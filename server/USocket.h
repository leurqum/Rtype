/*
** USocket.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
** 
** Made by marche_m (Maxime Marchès)
** Login   <marche_m@epitech.net>
** 
** Started on  Sat Dec 29 11:16:53 2012 marche_m (Maxime Marchès)
** Last update Sun Dec 30 14:01:04 2012 marche_m (Maxime Marchès)
*/

#ifndef __USOCKET__
# define __USOCKET__

#include <iostream>
#include <string>

#include "ISocket.h"

#define INVALID_SOCKET 0

class	USocket : public ISocket
{
public:
  virtual ~USocket();
  USocket();

  bool		connectToServer(std::string const & host, std::string const & port);
  bool		connectFromAcceptedFd(void * fd);
  int		recv(std::string & buffer, int blocksize);
  int		recv(s_protocol * package);
  int		sendv(std::string const & data);
  int		sendv(void * const & data, int const & size);
  int		sendv(s_protocol * const & package);

  int		getSocket() const { return _connectSocket };
private:
  struct hostent		* _server;

  std::string			_host;
  std::string			_port;
  struct sockaddr_in		_hints;
  int				_connectSocket;
  bool				_close;
}



#endif
