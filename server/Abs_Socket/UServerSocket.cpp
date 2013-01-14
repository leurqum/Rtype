//
// UServerSocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:31 2013 marche_m (Maxime Marchès)
// Last update Mon Jan 14 18:03:31 2013 marche_m (Maxime Marchès)
//

#include "UServerSocket.hpp"

void	UServerSocket::addNewPeer(void * sock)
{
  std::cout << "new Client !" << std::endl;
  ISocket * acc = this->myaccept(sock);
  if (acc->isUDP() == true)
    {
      this->_clientsSocksMap[((USocket *)(acc))->getSocket()] = acc;
      return ;
    }
  this->_clientsList.push_back(((USocket *)(acc))->getSocket());
  this->_clientsSocksMap[((USocket *)(acc))->getSocket()] = acc;
}

int		UServerSocket::selectSockets()
{
  int		nbSocksReady;
  int		maxFd = 0;

  FD_ZERO(&_readFd);
  for (std::list<int>::iterator it = _clientsList.begin(); it != _clientsList.end(); it++)
    {
      if (maxFd < *it)
	maxFd = *it;
      FD_SET((*it), &_readFd);
    }
  if ((nbSocksReady = select(maxFd + 1, &_readFd, NULL, NULL, 0)) == -1)
    {
      std::cerr << "Server select() error: " << std::endl;
      return -1;
    }
  return nbSocksReady;
}

void	UServerSocket::callBack(std::list<int>::iterator & it)
{
  std::cout << "start callBack" << std::endl;

  ISocket * tmp = _clientsSocksMap[*it];
  void	* data = 0;
  void	* header = 0;

  if (!tmp->recv(&header, &data))
    {
      std::cout << "client disconnected" << std::endl;
      it = _clientsList.erase(it);
      _clientsSocksMap.erase(((USocket*)(tmp))->getSocket());
      delete tmp;
      it--;
      std::cout << "end callBack" << std::endl;
      return ;
    }
  this->_interPckg->executeCmd(header, data, tmp);
  std::cout << "end callBack" << std::endl;
}

void	UServerSocket::launch()
{
  std::cout << "server launched !" << std::endl;
  _clientsList.push_back(_listenSocketTcp);
  _clientsList.push_back(_listenSocketUdp);
  while (true)
    {
      int nbSocksReady = this->selectSockets();
      for (std::list<int>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
	if (FD_ISSET((*it), &_readFd))
	  {
	    nbSocksReady--;
	    if ((*it) == _listenSocketTcp)
	      this->addNewPeer(&(*it)); // TODO udp / tcp
	    else if ((*it) == _listenSocketUdp)
	      {
		this->addNewPeer(&(*it));
		this->callBack(it);
		_clientsSocksMap.erase(*it);
	      }
	    else
	      this->callBack(it);
	  }
    }
}

ISocket	* UServerSocket::myaccept(void * sockType)
{
  int			acceptSock;
  struct sockaddr	saClient;
  int			clientSize = sizeof(saClient);

  if ((*((int *)sockType)) == this->_listenSocketUdp)
    {
      ISocket * ret = new USocket();
      ret->setUDP(true);
      ret->connectFromAcceptedFd(((int *)sockType));
      return ret;
    }
  acceptSock = accept(*((int *)sockType), &saClient, (socklen_t *)&clientSize);
  if (acceptSock <= 0) {
    std::cerr << "accept failed with error: " << std::endl;
    return NULL;
  }
  ISocket * ret = new USocket();
  ret->connectFromAcceptedFd(&acceptSock);
  return ret;
}

bool	UServerSocket::init(std::string const & listenHost, std::string const & listenPort)
{
  int	i;
  std::stringstream ss;
  int port;

  ss << listenPort;
  ss >> port;
  ss.str("");
  ss.clear();
  // ========= TCP =========
  bzero((char *) &(this->_servAddr), sizeof(this->_servAddr));
  this->_servAddr.sin_family = AF_INET;
  this->_servAddr.sin_addr.s_addr = INADDR_ANY;
  this->_servAddr.sin_port = htons(port);
  this->_listenSocketTcp = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_listenSocketTcp <= 0)
    {
      std::cerr << "socket failed with error (TCP)" << std::endl;
      return false;
    }
  i = bind( this->_listenSocketTcp, (struct sockaddr *) &this->_servAddr, sizeof(this->_servAddr));
  if (i < 0)
    {
      std::cerr << "bind failed with error (TCP): " << std::endl;
      close(this->_listenSocketTcp);
      return false;
    }
  if (listen(_listenSocketTcp, 5) < 0)
    {
      std::cerr << "listen failed with error (TCP): " << std::endl;
      return false;
    }

  // ========== UDP =========
  bzero((char *) &(this->_servAddr), sizeof(this->_servAddr));
  this->_servAddr.sin_family = AF_INET;
  this->_servAddr.sin_addr.s_addr = INADDR_ANY;
  this->_servAddr.sin_port = htons(port + 1);
  this->_listenSocketUdp = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->_listenSocketUdp <= 0)
    {
      std::cerr << "socket failed with error (UDP)" << std::endl;
      return false;
    }
  i = bind( this->_listenSocketUdp, (struct sockaddr *) &this->_servAddr, sizeof(this->_servAddr));
  if (i < 0)
    {
      std::cerr << "bind failed with error (UDP): " << std::endl;
      close(this->_listenSocketUdp);
      return false;
    }

  return true;
}

UServerSocket::~UServerSocket()
{
  if (this->_listenSocketTcp)
    close(this->_listenSocketTcp);
  if (this->_listenSocketUdp)
    close(this->_listenSocketUdp);
}

UServerSocket::UServerSocket(Server *s)
{
  _interPckg = new InterpretPackage(s);
  this->_listenSocketTcp = 0;
  this->_listenSocketUdp = 0;
}
