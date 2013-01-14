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
	if (acc->isUDP() == true)
	{
		this->_clientsSocksMap[((WSocket *)(acc))->getSocket()] = acc;
		return ;
	}
	this->_clientsList.push_back(((WSocket *)(acc))->getSocket());
	this->_clientsSocksMap[((WSocket *)(acc))->getSocket()] = acc;
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
	_clientsList.push_back(_listenSocketUdp);

	while (true)
	{
		int nbSocksReady = this->selectSockets();
		for (std::list<SOCKET>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
			if (FD_ISSET((*it), &_readFd))
			{
				nbSocksReady--;
				if ((*it) == _listenSocketTcp)
					this->addNewPeer(&(*it));
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

ISocket	* WServerSocket::myaccept(void * sockType)
{
	SOCKET				acceptSock;
	struct sockaddr_in	saClient;
	int					clientSize = sizeof(saClient);

	if ((*((int *)sockType)) == this->_listenSocketUdp)
    {
		ISocket * ret = new WSocket();
		ret->setUDP(true);
		ret->connectFromAcceptedFd(((int *)sockType));
		return ret;
    }

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

  // ========== UDP =========
  memset((char *) &(this->_servAddr), 0, sizeof(this->_servAddr));
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
      closesocket(this->_listenSocketUdp);
      return false;
    }

  return true;
//	struct addrinfo hints;
//	WSADATA			wsd;
//	int				i;
//	struct addrinfo *result = NULL;
//
//	if ((i = WSAStartup(MAKEWORD(2, 2), &wsd)))
//	{
//        std::cerr << "Unable to load Winsock: " << i << std::endl;
//        return false;
//    }
//	ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;
//
//    // Resolve the server address and port
//	i = getaddrinfo(NULL, listenPort.c_str(), &hints, &result);
////	i = getaddrinfo(listenHost.c_str(), listenPort.c_str(), &hints, &result);
//    if ( i != 0 ) {
//        std::cerr << "getaddrinfo failed with error: " << i << std::endl;
//        return false;
//    }
//
//    this->_listenSocket = WSASocket(result->ai_family, result->ai_socktype, result->ai_protocol, NULL, 0, 0);
//    if (this->_listenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        return false;
//    }
//
//    // Setup the TCP listening socket
//    i = bind( this->_listenSocket, result->ai_addr, (int)result->ai_addrlen);
//    if (i == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//        closesocket(this->_listenSocket);
//        return false;
//    }
//    if (listen(_listenSocket, 1) == SOCKET_ERROR) {
//        std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
//        return false;
//    }
//	return true;
}

WServerSocket::~WServerSocket()
{
	if (this->_listenSocketTcp != INVALID_SOCKET)
		closesocket(this->_listenSocketTcp);
	if (this->_listenSocketUdp != INVALID_SOCKET)
		closesocket(this->_listenSocketUdp);
	WSACleanup();
}

WServerSocket::WServerSocket(Server * s)
{
	this->_interPckg = new InterpretPackage(s);
	this->_listenSocketTcp = INVALID_SOCKET;
	this->_listenSocketUdp = INVALID_SOCKET;
}
