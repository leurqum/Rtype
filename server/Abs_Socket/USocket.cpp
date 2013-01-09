//
// USocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Dec 29 11:22:15 2012 marche_m (Maxime Marchès)
// Last update Wed Jan  9 17:46:55 2013 marche_m (Maxime Marchès)
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

int		USocket::recv(void ** header, void ** data)
{
  int	ret;
  *header = new int[2];

  ret = read(this->_connectSocket, *header, (2 * sizeof(int)));
  if (ret <= 0)
    return ret;
  *data = new char[((int *)(*header))[1]];
  memset(*data, 0, ((int *)(*header))[1]);
  ret = read(this->_connectSocket, *data, ((int *)(*header))[1]);
  if (ret <= 0)
    return ret;
  return 1;
  // int	* headerTmp = new int[2];
  // char	* dataTmp = 0;
  // int	ret;

  // ret = read(this->_connectSocket, headerTmp, (2 * sizeof(int)));
  // if (ret <= 0)
  //   return ret;
  // dataTmp = new char[headerTmp[1]];
  // memset(dataTmp, 0, headerTmp[1]);
  // ret = read(this->_connectSocket, dataTmp, headerTmp[1]);
  // if (ret <= 0)
  //   return ret;
  // header = headerTmp;
  // data = dataTmp;
  // return 1;
}

int		USocket::sendv(std::string const & data)
{
  return write(this->_connectSocket, data.c_str(), data.size());
}

int		USocket::sendv(int size, void * data)
{
  return write(this->_connectSocket, data, size);
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
