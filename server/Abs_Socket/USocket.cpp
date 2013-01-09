//
// USocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Dec 29 11:22:15 2012 marche_m (Maxime Marchès)
// Last update Wed Jan  9 09:56:23 2013 marche_m (Maxime Marchès)
//

#include "USocket.hpp"

USocket::USocket()
{
  _connectSocket = INVALID_SOCKET;
  _close = true;
  _udp = IPPROTO_TCP;
}

void	USocket::setUDP(bool val)
{
  if (val == true)
    _udp = IPPROTO_UDP;
  else
    _udp = IPPROTO_TCP;
}

bool	USocket::connectToServer(std::string const & host, std::string const & port)
{
  this->_host = host;
  this->_port = port;

  this->_connectSocket = socket(AF_INET, SOCK_STREAM, _udp);
  if (this->_connectSocket < 0)
    {
      std::cerr << "error: socket" << std::endl;
      return 0;
    }
  if ((this->_server = gethostbyname(this->_host.c_str())) == NULL)
    {
      std::cerr << "error: gethostbyname no such host" << this->_host << std::endl;
      return 0;
    }
  bzero((char *) &this->_hints, sizeof(this->_hints));
  this->_hints.sin_family = AF_INET;
  bcopy((char *)this->_server->h_addr, (char *)&this->_hints.sin_addr.s_addr, this->_server->h_length);
  this->_hints.sin_port = htons(atoi(this->_port.c_str()));
  if (connect(this->_connectSocket,(struct sockaddr *) &this->_hints,sizeof(this->_hints)) < 0)
    {
      std::cerr << "ERROR connecting" << std::endl;
      return false;
    }
  return true;
}


bool	USocket::connectFromAcceptedFd(void * fd)
{
  int * sock = static_cast<int *>(fd);

  this->_connectSocket = *sock;
  this->_close = false;
  return true;
}

int		USocket::recv()
{
  char toto[4242];
  memset(toto, 0, 4242);
  int ret = read(this->_connectSocket, toto, 4242);
  if (ret <= 0)
    return ret;
  std::cout << toto << std::endl;
  return 1;
}

int		USocket::sendv(std::string const & data)
{
  write(this->_connectSocket, data.c_str(), data.size());
}

USocket::~USocket()
{
  close(this->_connectSocket);

  //Connect from accepted fd
  if (this->_close == true)
    {
      //      WSACleanup();
      //      freeaddrinfo(this->_results);
    }
}
