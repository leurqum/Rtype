#include "WSocket.hpp"

std::wstring StringToWString(const std::string& s)
{
  std::wstring temp(s.length(), L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

WSocket::WSocket()
{
	_connectSocket = INVALID_SOCKET;
	_WSAClose = true;

}

bool WSocket::connectToServer(std::string const & host, std::string const & port)
{
	this->_host = host;
	this->_port = port;

	WSADATA			wsd;
	DWORD			dwFlags = 0;
	int				rc;

    if ((rc = WSAStartup(MAKEWORD(2, 2), &wsd)))
	{
        std::cerr << "Unable to load Winsock: " << rc << std::endl;
        return false;
    }

	//Init of struct addrinfo
    ZeroMemory((PVOID) &this->_hints, sizeof((this->_hints)));
    this->_hints.ai_family = AF_INET;
    this->_hints.ai_socktype = SOCK_STREAM;
    this->_hints.ai_protocol = IPPROTO_TCP;


	if ((rc = getaddrinfo(host.c_str(), port.c_str(), &(this->_hints), (&this->_results))) != 0 )
	{
        std::cerr << "getaddrinfo failed with error: " << rc << std::endl;
        return false;
    }
	if ((this->_connectSocket = WSASocket(this->_results->ai_family, this->_results->ai_socktype, this->_results->ai_protocol, NULL, 0, 0)) == INVALID_SOCKET)
	{
		std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
		return false;
	}
	WSAConnect(this->_connectSocket, this->_results->ai_addr, this->_results->ai_addrlen, 0, 0, 0, 0);
	return true;
}


bool WSocket::connectFromAcceptedFd(void * fd)
{
	SOCKET * sock = static_cast<SOCKET *>(fd);

	this->_connectSocket = *sock;
	this->_WSAClose = false;
	return true;
}

int WSocket::recv(s_protocol * package)
{
	WSABUF			buf;
	int				rc, err;
	DWORD			recvBytes, flags;
	WSAOVERLAPPED	recvOverlapped;

	buf.len = 2 * sizeof(int);
	buf.buf= new char[buf.len];
	ZeroMemory(buf.buf, buf.len);
	flags = 0;
	SecureZeroMemory((PVOID) & recvOverlapped, sizeof (WSAOVERLAPPED));
	// Create an event handle and setup an overlapped structure.
    recvOverlapped.hEvent = WSACreateEvent();
    if (recvOverlapped.hEvent == NULL) {
        std::cerr << "WSACreateEvent failed: " << WSAGetLastError() << std::endl;
        return 0;
    }

	rc = WSARecv(this->_connectSocket, &buf, 1, &recvBytes, &flags, &recvOverlapped, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		std::cerr << "WSARecv failed with error: " << err << std::endl;
		return 0;
	}
	if (recvBytes == 0)
	{
		std::cout << "Socket disconected" << std::endl;
		return 0;
	}
	
	package->cmdId = ((int*)buf.buf)[0];
	package->size = ((int*)buf.buf)[1];
	delete buf.buf;
	buf.len = package->size;
	buf.buf = new char[buf.len];
	rc = WSARecv(this->_connectSocket, &buf, 1, &recvBytes, &flags, &recvOverlapped, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		std::cerr << "WSARecv failed with error: " << err << std::endl;
		return 0;
	}
	package->data = buf.buf;
	WSAResetEvent(recvOverlapped.hEvent);
	return 1;
}


int WSocket::recv(std::string & buffer, int blocksize)
{
	WSABUF			buf;
	int				rc, err;
	DWORD			recvBytes, flags;
	WSAOVERLAPPED	recvOverlapped;

	buf.len = blocksize;
	buf.buf= new char[buf.len];
	ZeroMemory(buf.buf, blocksize);
	flags = 0;
	SecureZeroMemory((PVOID) & recvOverlapped, sizeof (WSAOVERLAPPED));
	// Create an event handle and setup an overlapped structure.
    recvOverlapped.hEvent = WSACreateEvent();
    if (recvOverlapped.hEvent == NULL) {
        std::cerr << "WSACreateEvent failed: " << WSAGetLastError() << std::endl;
        return 0;
    }

	rc = WSARecv(this->_connectSocket, &buf, 1, &recvBytes, &flags, &recvOverlapped, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		std::cerr << "WSARecv failed with error: " << err << std::endl;
		return 0;
	}
	if (recvBytes == 0)
	{
		std::cout << "Socket disconected" << std::endl;
		return 0;
	}
	
	
	buffer = buf.buf;
	delete buf.buf;
	WSAResetEvent(recvOverlapped.hEvent);
	std::cout << "recv: |" << buffer << "|" << std::endl;
	return 1;
}

int WSocket::sendv(void * const & data, int const & size)
{
	send(this->_connectSocket, (char*)data, size, NULL);
	return 1;
}

int	WSocket::sendv(s_protocol * const & package)
{
	int * header = new int[2];
	void * data;
	header[0] = package->cmdId;
	header[1] = package->size;
	data = package->data;
	send(this->_connectSocket, (char*)header, 2 * sizeof(int), NULL);
	send(this->_connectSocket, (char*)data, header[1], NULL);
	delete header;
	return 1;
}

int WSocket::sendv(std::string const & data)
{
	int				err;
	int				rc;
	WSABUF			buf;
	DWORD			sendBytes;
	WSAOVERLAPPED	sendOverlapped;

	buf.len = data.length();
	buf.buf = new char[buf.len];
	SecureZeroMemory((PVOID) & sendOverlapped, sizeof (WSAOVERLAPPED));
	sendOverlapped.hEvent = WSACreateEvent();

	for (int i = 0; data[i]; i++)
		buf.buf[i] = data[i];

	if ((rc = WSASend(this->_connectSocket, &buf, 1, &sendBytes, 0, &sendOverlapped, NULL)) == SOCKET_ERROR &&
		(WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		std::cerr << "WSASend failed with error: " << err << std::endl;
		return 0;
	}
	std::cout << "send: " << data << std::endl;
	return rc;
}

WSocket::~WSocket()
{
	closesocket(this->_connectSocket);

	//Connect from accepted fd
	if (this->_WSAClose == true)
	{
		WSACleanup();
		freeaddrinfo(this->_results);
	}
}
