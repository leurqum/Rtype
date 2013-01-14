//
// USocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Dec 29 11:22:15 2012 marche_m (Maxime Marchès)
// Last update Sat Jan 12 15:58:54 2013 marche_m (Maxime Marchès)
//

#include "USocket.hpp"

USocket::USocket()
{
  _connectSocket = INVALID_SOCKET;
  _close = true;
  _udp = false;
}

void	USocket::setUDP(bool val)
{
  if (_connectSocket == INVALID_SOCKET)
    _udp = val;
  else
    std::cerr << "Socket: could not set udp while socket is already created" << std::endl;
}

bool	USocket::connectToServer(std::string const & host, std::string const & port)
{
  std::stringstream ss;
  int iPort;

  this->_host = host;
  this->_port = port;
  ss << _port;
  ss >> iPort;

  if (_udp == false)
    this->_connectSocket = socket(AF_INET, SOCK_STREAM, 0);
  else
    this->_connectSocket = socket(AF_INET, SOCK_DGRAM, 0);
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
  this->_hints.sin_port = htons(iPort);
  if (_udp == false)
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
  ssize_t	ret;
  *header = new int[2];

  if (_udp == false)
    {
      if ((ret = ::recv(this->_connectSocket, *header, 2 * sizeof(int), 0)) <= 0)
	return ret;
      *data = new char[((int *)(*header))[1]];
      memset(*data, 0, ((int *)(*header))[1]);
      if ((ret = ::recv(this->_connectSocket, *data, ((int *)(*header))[1], 0)) <= 0)
	return ret;
      return 1;
    }
  else
    {
      socklen_t tosize = sizeof(_hints);

      if ((ret = ::recvfrom(this->_connectSocket, *header, 2 * sizeof(int), 0, (struct sockaddr *)&_hints, &tosize)) <= 0)
	return ret;
      *data = new char[((int *)(*header))[1]];
      memset(*data, 0, ((int *)(*header))[1]);
      if ((ret = ::recvfrom(this->_connectSocket, *data, ((int *)(*header))[1], 0, (struct sockaddr *)&_hints, &tosize)) <= 0)
	return ret;
      return 1;
    }
}

int		USocket::sendv(std::string const & data)
{
  if (_udp == false)
    return ::send(this->_connectSocket, data.c_str(), data.size(), 0);
  else
    return ::sendto(this->_connectSocket, data.c_str(), data.size(), 0, (struct sockaddr *)&this->_hints, sizeof(this->_hints));
}

int		USocket::sendv(int size, void * data)
{
  if (_udp == false)
    return ::send(this->_connectSocket, data, size, 0);
  else
    return ::sendto(this->_connectSocket, data, size, 0, (struct sockaddr *)&this->_hints, sizeof(this->_hints));
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
