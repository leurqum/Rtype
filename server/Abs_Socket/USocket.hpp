/*
** USocket.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
** 
** Made by marche_m (Maxime Marchès)
** Login   <marche_m@epitech.net>
** 
** Started on  Sat Dec 29 11:16:53 2012 marche_m (Maxime Marchès)
// Last update Wed Jan  9 09:55:42 2013 marche_m (Maxime Marchès)
*/

#ifndef __USOCKET__
# define __USOCKET__

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <cstring>
#include <curses.h>
#include <errno.h>
#include <istream>
#include <netdb.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <term.h>
#include <unistd.h>
#include <list>

#include "ISocket.hpp"

#define INVALID_SOCKET 0

class	USocket : public ISocket
{
public:
  virtual ~USocket();
  USocket();

  bool		connectToServer(std::string const & host, std::string const & port);
  bool		connectFromAcceptedFd(void * fd);
  int		recv();
  int		sendv(std::string const & data);

  int		getSocket() const { return _connectSocket; }
  void		setUDP(bool val);
private:
  struct hostent		* _server;

  std::string			_host;
  std::string			_port;
  struct sockaddr_in		_hints;
  int				_connectSocket;
  bool				_close;
  int				_udp;
};



#endif
