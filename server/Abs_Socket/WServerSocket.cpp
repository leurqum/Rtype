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
	ISocket * acc = this->accept();
	this->_clientsList.push_back(((WSocket *)(acc))->getSocket());
	this->_clientsSocksMap[((WSocket *)(acc))->getSocket()] = acc;
}

int		WServerSocket::selectSockets()
{
	int		nbSocksReady;

	FD_ZERO(&_readFd);
	for (std::list<SOCKET>::iterator it = _clientsList.begin(); it != _clientsList.end(); it++)
		FD_SET((*it), &_readFd);
	if ((nbSocksReady = select(FD_SETSIZE, &_readFd, NULL, NULL, NULL)) == -1)
	{
		std::cerr << "Server select() error: " << WSAGetLastError() << std::endl;
		return -1;
	}
	return nbSocksReady;
}

void	WServerSocket::interpretCmd(std::list<SOCKET>::iterator & it)
{
	s_protocol * package = new s_protocol;

	ISocket * tmp = _clientsSocksMap[*it];
	if (!tmp->recv(package))
	{
		//Client disconnected
		it = _clientsList.erase(it); // pb ici
		_clientsSocksMap.erase(((WSocket*)(tmp))->getSocket());
		delete tmp;
		it--;
		return ;
	}
	std::cout << "------------ readCmd ------------" << std::endl;
	std::cout << "Commande ID: " << package->cmdId << std::endl;
	std::cout << "Size parameter: " << package->size << std::endl;
	std::cout << "Data: " << (char*)package->data << std::endl;
	std::cout << "---------------------------------" << std::endl;
	s_protocol * ret = _usersManager->executeCmd(package, tmp);
	if (ret != NULL)
	{
		std::cout << "------------ return package ------------" << std::endl;
		std::cout << "Commande ID: " << ret->cmdId << std::endl;
		std::cout << "Size parameter: " << ret->size << std::endl;
		std::cout << "Data: " << (char *)ret->data << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		tmp->sendv(ret);
		delete ret;
	}
	delete package;
}

void	WServerSocket::launch()
{
	std::cout << "server launched !" << std::endl;
	_clientsList.push_back(_listenSocket);

	while (true)
	{
		int nbSocksReady = this->selectSockets();
		for (std::list<SOCKET>::iterator it = _clientsList.begin(); nbSocksReady > 0 && it != _clientsList.end(); it++)
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

ISocket	* WServerSocket::accept()
{
	SOCKET				acceptSock;
	struct sockaddr_in	saClient;
	int					clientSize = sizeof(saClient);

	acceptSock = WSAAccept(
		this->_listenSocket,
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

bool	WServerSocket::init(std::string const & listenHost, std::string const & listenPort, UsersManager * usersManager)
{
	struct addrinfo hints;
	WSADATA			wsd;
	int				i;
	struct addrinfo *result = NULL;

	if ((i = WSAStartup(MAKEWORD(2, 2), &wsd)))
	{
        std::cerr << "Unable to load Winsock: " << i << std::endl;
        return false;
    }
	ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
	i = getaddrinfo(NULL, listenPort.c_str(), &hints, &result);
//	i = getaddrinfo(listenHost.c_str(), listenPort.c_str(), &hints, &result);
    if ( i != 0 ) {
        std::cerr << "getaddrinfo failed with error: " << i << std::endl;
        return false;
    }

    this->_listenSocket = WSASocket(result->ai_family, result->ai_socktype, result->ai_protocol, NULL, 0, 0);
    if (this->_listenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        return false;
    }

    // Setup the TCP listening socket
    i = bind( this->_listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (i == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(this->_listenSocket);
        return false;
    }
    if (listen(_listenSocket, 1) == SOCKET_ERROR) {
        std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }
	_usersManager = usersManager;
	return true;
}

WServerSocket::~WServerSocket()
{
	closesocket(this->_listenSocket);
	delete _usersManager;
	WSACleanup();
}

WServerSocket::WServerSocket()
{
	this->_listenSocket = INVALID_SOCKET;
}
