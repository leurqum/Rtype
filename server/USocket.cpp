//
// USocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Dec 29 11:22:15 2012 marche_m (Maxime Marchès)
// Last update Sun Dec 30 14:03:22 2012 marche_m (Maxime Marchès)
//

#include "USocket.h"

USocket::USocket()
{
  _connectSocket = INVALID_SOCKET;
  _close = true;
}

bool	USocket::connectToServer(std::string const & host, std::string const & port)
{
  this->_host = host;
  this->_port = port;

  this->_connectSocket = socket(AF_INET, SOCK_STREAM, 0);
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
  bzero((char *) &this->hints, sizeof(this->_hints));
  this->_hints.sin_family = AF_INET;
  bcopy((char *)this->_server->h_addr, (char *)&this->_hints.sin_addr.s_addr, this->_server->h_length);
  this->_hints.sin_port = htons(atoi(this->portNo));
  if (connect(this->sockFd,(struct sockaddr *) &this->servAddr,sizeof(this->servAddr)) < 0)
    this->error("ERROR connecting");

  /*
    WSADATA			wsd;
    DWORD			dwFlags = 0;
    int				rc;

    if ((rc = WSAStartup(MAKEWORD(2, 2), &wsd)))
    {
    std::cerr << "Unable to load Winsock: " << rc << std::endl;
    return false;
    }

    //Init of struct addrinfo
    ZeroMemory((PVOID) &this->_hints, sizeof((this->_hints)));
    this->_hints.ai_family = AF_INET;
    this->_hints.ai_socktype = SOCK_STREAM;
    this->_hints.ai_protocol = IPPROTO_TCP;


    if ((rc = getaddrinfo(host.c_str(), port.c_str(), &(this->_hints), (&this->_results))) != 0 )
    {
    std::cerr << "getaddrinfo failed with error: " << rc << std::endl;
    return false;
    }
    if ((this->_connectSocket = WSASocket(this->_results->ai_family, this->_results->ai_socktype, this->_results->ai_protocol, NULL, 0, 0)) == INVALID_SOCKET)
    {
    std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
    return false;
    }
    WSAConnect(this->_connectSocket, this->_results->ai_addr, this->_results->ai_addrlen, 0, 0, 0, 0);
  */
  return true;
}


bool	USocket::connectFromAcceptedFd(void * fd)
{
  int * sock = static_cast<int *>(fd);

  this->_connectSocket = *sock;
  this->_close = false;
  return true;
}

int	USocket::recv(s_protocol * package)
{
}


int	USocket::recv(std::string & buffer, int blocksize)
{
}

int	USocket::sendv(void * const & data, int const & size)
{
}

int	USocket::sendv(s_protocol * const & package)
{
  int * header = new int[2];
  void * data;
  header[0] = package->cmdId;
  header[1] = package->size;
  data = package->data;
  send(this->_connectSocket, (char*)header, 2 * sizeof(int), NULL);
  send(this->_connectSocket, (char*)data, header[1], NULL);
  delete header;
  return 1;
}

int	USocket::sendv(std::string const & data)
{
}

USocket::~USocket()
{
  closesocket(this->_connectSocket);

  //Connect from accepted fd
  if (this->_close == true)
    {
      //      WSACleanup();
      freeaddrinfo(this->_results);
    }
}
