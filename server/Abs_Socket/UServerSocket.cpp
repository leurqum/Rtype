//
// UServerSocket.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Sat Jan  5 16:52:31 2013 marche_m (Maxime Marchès)
// Last update Mon Jan  7 16:30:25 2013 marche_m (Maxime Marchès)
//

#include "UServerSocket.h"

void	UServerSocket::addNewPeer(void * peer)
{
  std::cout << "new Client !" << std::endl;
  ISocket * acc = this->myaccept();
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
      std::cout << "client" << std::endl;
      FD_SET((*it), &_readFd);
    }
  if ((nbSocksReady = select(maxFd + 1, &_readFd, NULL, NULL, 0)) == -1)
    {
      std::cerr << "Server select() error: " << std::endl;
      return -1;
    }
  std::cout << "select:" << nbSocksReady << std::endl;
  return nbSocksReady;
}

void	UServerSocket::interpretCmd(std::list<int>::iterator & it)
{
  std::cout << "New commad !" << std::endl;
  // s_protocol * package = new s_protocol;

  ISocket * tmp = _clientsSocksMap[*it];
  if (!tmp->recv())
    {
      //Client disconnected
      it = _clientsList.erase(it); // pb ici
      _clientsSocksMap.erase(((USocket*)(tmp))->getSocket());
      delete tmp;
      it--;
      return ;
    }
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
	      this->interpretCmd(it);
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

  this->_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
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

UServerSocket::UServerSocket()
{
  this->_listenSocket = 0;
}
