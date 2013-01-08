#ifndef __WSOCKET__
# define __WSOCKET__

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
# include <string>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


# include "ISocket.h"

std::wstring	StringToWString(const std::string& s);

class WSocket : public ISocket
{
public:
	virtual	~WSocket();
	WSocket();

	bool				connectToServer(std::string const & host, std::string const & port);
	bool				connectFromAcceptedFd(void * fd);
	int					recv(std::string & buffer, int blocksize);
	int					recv(s_protocol * package);
	int					sendv(std::string const & data);
	int					sendv(void * const & data, int const & size);
	int					sendv(s_protocol * const & package);

	SOCKET				getSocket() const { return _connectSocket };
private:
	std::string			_host;
	std::string			_port;
	struct addrinfo		_hints;
	struct addrinfo		* _results;
	SOCKET				_connectSocket;
	bool				_WSAClose;
};


#endif