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

#include "IServerSocket.hpp"
#include "./../../protocol.h"
#include "../src/include/InterpretPackage.hpp"

class WServerSocket : public IServerSocket
{
public:
	WServerSocket(Server * s);
	virtual						~WServerSocket();
	bool						init(std::string const & listenHost, std::string const & listenPort);
	ISocket						* myaccept(void * sockType);
	void						launch();

private:
	void						addNewPeer(void * peer);
	SOCKET						getSocketTcp() { return _listenSocketTcp; }
//	SOCKET						getSocketUdp() { return _listenSocketUdp; }
	int							selectSockets();
	void						callBack(std::list<SOCKET>::iterator & it);

	SOCKET						_listenSocketTcp;
//	SOCKET						_listenSocketUdp;
	std::list<SOCKET>			_clientsList;
	std::map<SOCKET, ISocket *>	_clientsSocksMap;
	fd_set						_readFd;
	InterpretPackage *			_interPckg;
	struct sockaddr_in			_servAddr;
	Server						* _server;
};

