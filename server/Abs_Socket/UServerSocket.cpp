//
// UServerSocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:31 2013 marche_m (Maxime Marchès)
// Last update Tue Jan 15 17:04:16 2013 marche_m (Maxime Marchès)
//

#include "UServerSocket.hpp"

void	UServerSocket::addNewPeer(void * peer)
{
  std::cout << "new Client !" << std::endl;
  ISocket * acc = this->myaccept(peer);
  ISocket * sockUdp = new USocket();
  sockUdp->setUDP(true);
  sockUdp->connectToServer(acc->getHost(), "4243");
  this->_server->createPlayerWaiting(this->_server->getGameList().size(), acc->getHost(), acc, sockUdp);

  this->_clientsList.push_back(((USocket *)(acc))->getSocket());
  this->_clientsSocksMap[((USocket *)(acc))->getSocket()] = acc;

	// TODO : voir si select sur l'udp est clean
	this->_clientsList.push_back(((WSocket *)(sockUdp))->getSocket());
	this->_clientsSocksMap[((WSocket *)(sockUdp))->getSocket()] = sockUdp;
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

  if (tmp->isUDP() == true)
    {
      header = new int[2];
      ((int*)header)[1] = sizeof(Protocol::cmd_client);
    }
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
  if (data)
    delete (char *)data;
  if (header)
    delete (int *)header;
  std::cout << "end callBack" << std::endl;
  // std::cout << "start callBack" << std::endl;

  // ISocket * tmp = _clientsSocksMap[*it];
  // void	* data = 0;
  // void	* header = 0;

  // if (!tmp->recv(&header, &data))
  //   {
  //     std::cout << "client disconnected" << std::endl;
  //     it = _clientsList.erase(it);
  //     _clientsSocksMap.erase(((USocket*)(tmp))->getSocket());
  //     delete tmp;
  //     it--;
  //     std::cout << "end callBack" << std::endl;
  //     return ;
  //   }
  // this->_interPckg->executeCmd(header, data, tmp);
  // std::cout << "end callBack" << std::endl;
}

void	UServerSocket::launch()
{
  std::cout << "server launched !" << std::endl;
  _clientsList.push_back(_listenSocketTcp);

  while (true)
    {
      int nbSocksReady = this->selectSockets();
      for (std::list<int>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
	if (FD_ISSET((*it), &_readFd))
	  {
	    nbSocksReady--;
	    if ((*it) == _listenSocketTcp)
	      this->addNewPeer(&(*it));
	    else
	      this->callBack(it);
	  }
    }
}

ISocket	* UServerSocket::myaccept(void * sockType)
{
  int			acceptSock;
  struct sockaddr_in	saClient;
  int			clientSize = sizeof(saClient);

  acceptSock = accept(*((int *)sockType), (struct sockaddr *)&saClient, (socklen_t *)&clientSize);
  if (acceptSock <= 0) {
    std::cerr << "accept failed with error: " << std::endl;
    return NULL;
  }

  ISocket * ret = new USocket();
  ret->connectFromAcceptedFd(&acceptSock);
  ret->setHost(inet_ntoa(saClient.sin_addr));
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
  return true;
}

UServerSocket::~UServerSocket()
{
  if (this->_listenSocketTcp != INVALID_SOCKET)
    close(this->_listenSocketTcp);
}

UServerSocket::UServerSocket(Server *s)
{
  _interPckg = new InterpretPackage(s);
  this->_listenSocketTcp = INVALID_SOCKET;
}
