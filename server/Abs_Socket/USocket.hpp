/*
// USocket.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Dec 29 11:16:53 2012 marche_m (Maxime Marchès)
// Last update Fri Jan 18 15:05:23 2013 mathieu leurquin
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

# define INVALID_SOCKET 0
# define UNUSED  __attribute__((__unused__))

class	USocket : public ISocket
{
public:
  virtual ~USocket();
  USocket();

  bool			connectToServer(std::string const & host, std::string const & port);
  bool			connectFromAcceptedFd(void * fd);
  int			recv(void ** header, void ** data);
  int			sendv(std::string const & data);
  int			sendv(int const & size, void * const & data);
  int			getSocket() const { return _connectSocket; }
  void			setUDP(bool const & val);
  bool			isUDP() const { return _udp; }
  void			setHost(std::string const & ip);
  std::string const &	getHost() const;

private:
  struct hostent		* _server;

  std::string			_host;
  std::string			_port;
  struct sockaddr_in		_hints;
  int				_connectSocket;
  bool				_close;
  bool				_udp;
};



#endif
