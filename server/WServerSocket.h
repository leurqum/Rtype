#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
# include <string>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <map>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include "IServerSocket.h"
#include "protocol.h"
#include "UsersManager.h"

class WServerSocket : public IServerSocket
{
public:
	WServerSocket();
	virtual						~WServerSocket();
	bool						init(std::string const & listenHost, std::string const & listenPort, UsersManager * usersManager);
	ISocket						* accept();
	void						launch();

private:
	void						addNewPeer(void * peer);
	SOCKET						getSocket() { return _listenSocket; }
	int							selectSockets();
	void						interpretCmd(std::list<SOCKET>::iterator & it);

	SOCKET						_listenSocket;
	std::list<SOCKET>			_clientsList;
	std::map<SOCKET, ISocket *>	_clientsSocksMap;
	UsersManager				* _usersManager;
	fd_set						_readFd;
};

