#include <sstream>
#include "WSocket.hpp"
#include "WServerSocket.hpp"

int CALLBACK conditionAcceptFunc(
    LPWSABUF lpCallerId,
    LPWSABUF lpCallerData,
    LPQOS pQos,
    LPQOS lpGQOS,
    LPWSABUF lpCalleeId,
    LPWSABUF lpCalleeData,
    GROUP FAR * g,
    DWORD_PTR dwCallbackData
    )
{
	return CF_ACCEPT;
}

void	WServerSocket::addNewPeer(void * peer)
{
	std::cout << "new Client !" << std::endl;
	ISocket * acc = this->myaccept(peer);
	ISocket * sockUdp = new WSocket();
	sockUdp->setUDP(true);
	sockUdp->connectToServer(acc->getHost(), "4243");
	this->_server->createPlayerWaiting(this->_server->getGameList().size(), acc->getHost(), acc, sockUdp);

	this->_clientsList.push_back(((WSocket *)(acc))->getSocket());
	this->_clientsSocksMap[((WSocket *)(acc))->getSocket()] = acc;

	// TODO : voir si select sur l'udp est clean
	this->_clientsList.push_back(((WSocket *)(sockUdp))->getSocket());
	this->_clientsSocksMap[((WSocket *)(sockUdp))->getSocket()] = sockUdp;
}

int		WServerSocket::selectSockets()
{
	int		nbSocksReady;
	int		maxFd = 0;

	FD_ZERO(&_readFd);
	for (std::list<SOCKET>::iterator it = _clientsList.begin(); it != _clientsList.end(); it++)
		FD_SET((*it), &_readFd);
	if ((nbSocksReady = select(maxFd + 1, &_readFd, NULL, NULL, NULL)) == -1)
	{
		std::cerr << "Server select() error: " << WSAGetLastError() << std::endl;
		return -1;
	}
	return nbSocksReady;
}

void	WServerSocket::callBack(std::list<SOCKET>::iterator & it)
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
		  _clientsSocksMap.erase(((WSocket*)(tmp))->getSocket());
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
}

void	WServerSocket::launch()
{
	std::cout << "server launched !" << std::endl;
	_clientsList.push_back(_listenSocketTcp);

	while (true)
	{
		int nbSocksReady = this->selectSockets();
		for (std::list<SOCKET>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
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

ISocket	* WServerSocket::myaccept(void * sockType)
{
	SOCKET				acceptSock;
	sockaddr_in			saClient;
	int					clientSize = sizeof(saClient);


	acceptSock = WSAAccept(
		(*((SOCKET*)sockType)),
		(SOCKADDR*) &saClient,
		&clientSize,
		&conditionAcceptFunc,
		NULL
	);
    if (acceptSock == INVALID_SOCKET) {
        std::cerr << "accept failed with error: " << WSAGetLastError() << std::endl;
        return NULL;
    }

	ISocket * ret = new WSocket();
	ret->connectFromAcceptedFd(&acceptSock);
	ret->setHost(inet_ntoa(saClient.sin_addr));
	return ret;
}

bool	WServerSocket::init(std::string const & listenHost, std::string const & listenPort)
{
	int					i;
	std::stringstream	ss;
	int					port;
	WSADATA				wsd;

	if ((i = WSAStartup(MAKEWORD(2, 2), &wsd)))
	{
        std::cerr << "Unable to load Winsock: " << i << std::endl;
        return false;
	}
	ss << listenPort;
	ss >> port;
	ss.str("");
	ss.clear();
	// ========= TCP =========
	_listenSocketTcp = socket(AF_INET, SOCK_STREAM, 0);
	if(_listenSocketTcp == INVALID_SOCKET)
	{
		std::cerr << "socket error" << std::endl;
		perror("socket()");
	    exit(errno);
	}


  memset((char *) &(this->_servAddr), 0, sizeof(this->_servAddr));
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
      closesocket(this->_listenSocketTcp);
      return false;
    }
  if (listen(_listenSocketTcp, 5) < 0)
    {
      std::cerr << "listen failed with error (TCP): " << std::endl;
      return false;
    }
  return true;
}

WServerSocket::~WServerSocket()
{
	if (this->_listenSocketTcp != INVALID_SOCKET)
		closesocket(this->_listenSocketTcp);
	WSACleanup();
}

WServerSocket::WServerSocket(Server * s)
{
	this->_interPckg = new InterpretPackage(s);
	this->_server = s;
	this->_listenSocketTcp = INVALID_SOCKET;
}
