//
// UServerSocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:31 2013 marche_m (Maxime Marchès)
// Last update Fri Jan 11 19:19:35 2013 mathieu leurquin
//

#include "UServerSocket.hpp"

void	UServerSocket::addNewPeer(void * peer)
{
  peer = peer;
  std::cout << "new Client !" << std::endl;
  ISocket * acc = this->myaccept();
  this->_clientsList.push_back(((USocket *)(acc))->getSocket());
  this->_clientsSocksMap[((USocket *)(acc))->getSocket()] = acc;
}

void		UServerSocket::setUDP(bool val)
{
  (val == true) ? (_udp = IPPROTO_UDP) : (_udp = IPPROTO_TCP);
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
  // s_protocol * package = new s_protocol;

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
  if (data)
    delete data;
  if (header)
    delete header;
  std::cout << "end callBack" << std::endl;
  // std::cout << "------------ readCmd ------------" << std::endl;
  // std::cout << "Commande ID: " << package->cmdId << std::endl;
  // std::cout << "Size parameter: " << package->size << std::endl;
  // std::cout << "Data: " << (char*)package->data << std::endl;
  // std::cout << "---------------------------------" << std::endl;
  // s_protocol * ret = _usersManager->executeCmd(package, tmp);
  // if (ret != NULL)
  //   {
  //     std::cout << "------------ return package ------------" << std::endl;
  //     std::cout << "Commande ID: " << ret->cmdId << std::endl;
  //     std::cout << "Size parameter: " << ret->size << std::endl;
  //     std::cout << "Data: " << (char *)ret->data << std::endl;
  //     std::cout << "----------------------------------------" << std::endl;
  //     tmp->sendv(ret);
  //     delete ret;
  //   }
  // delete package;
}

void	UServerSocket::launch()
{
  std::cout << "server launched !" << std::endl;
  _clientsList.push_back(_listenSocket);

  while (true)
    {
      int nbSocksReady = this->selectSockets();
      for (std::list<int>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
	if (FD_ISSET((*it), &_readFd))
	  {
	    nbSocksReady--;
	    if ((*it) == _listenSocket)
	      this->addNewPeer(&(*it));
	    else
	      this->callBack(it);
	  }
    }
}

ISocket	* UServerSocket::myaccept()
{
  int		acceptSock;
  struct sockaddr	saClient;
  int			clientSize = sizeof(saClient);

  acceptSock = accept(this->_listenSocket, &saClient, (socklen_t *)&clientSize);
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
  int port = atoi(listenPort.c_str());

  bzero((char *) &(this->_servAddr), sizeof(this->_servAddr));
  this->_servAddr.sin_family = AF_INET;
  this->_servAddr.sin_addr.s_addr = INADDR_ANY;
  this->_servAddr.sin_port = htons(port);

  this->_listenSocket = socket(AF_INET, SOCK_STREAM, this->_udp);
  if (this->_listenSocket <= 0)
    {
      std::cerr << "socket failed with error" << std::endl;
      return false;
    }

  // Setup the TCP listening socket
  // TODO: probleme deuxieme argument
  i = bind( this->_listenSocket, (struct sockaddr *) &this->_servAddr, sizeof(this->_servAddr));
  if (i < 0)
    {
      std::cerr << "bind failed with error: " << std::endl;
      close(this->_listenSocket);
      return false;
    }
  if (listen(_listenSocket, 5) < 0)
    {
      std::cerr << "listen failed with error: " << std::endl;
      return false;
    }
  return true;
}

UServerSocket::~UServerSocket()
{
  close(this->_listenSocket);
}

UServerSocket::UServerSocket(Server *s)
{
  _interPckg = new InterpretPackage(s);
  this->_listenSocket = 0;
  this->_udp = IPPROTO_TCP;
}
