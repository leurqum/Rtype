#include <sstream>
#include "./../../protocol.h"
#include "WSocket.hpp"

std::wstring StringToWString(const std::string& s)
{
  std::wstring temp(s.length(), L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

void	WSocket::setHost(std::string const & host)
{
	_host = host;
}

std::string const & WSocket::getHost() const
{
	return _host;
}

WSocket::WSocket()
{
	_connectSocket = INVALID_SOCKET;
	_WSAClose = true;
	_udp = false;
	_host = "";
}

void WSocket::setUDP(bool const & val)
{
if (_connectSocket == INVALID_SOCKET)
    _udp = val;
  else
    std::cerr << "Socket: could not set udp while socket is already created" << std::endl;
}

bool WSocket::connectToServer(std::string const & host, std::string const & port)
{
	std::stringstream ss;
	int iPort;

	this->_host = host;
	this->_port = port;
	ss << _port;
	ss >> iPort;

	if (_udp == false)
		this->_connectSocket = socket(AF_INET, SOCK_STREAM, 0);
	else
		this->_connectSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (this->_connectSocket < 0)
	{
		std::cerr << "error: socket" << std::endl;
		return 0;
    }
	if ((this->_server = gethostbyname(this->_host.c_str())) == NULL)
    {
		std::cerr << "error: gethostbyname no such host" << this->_host << std::endl;
		return 0;
    }
	memset((char *) &this->_hints, 0, sizeof(this->_hints));
	this->_hints.sin_family = AF_INET;
	memcpy((char *)this->_server->h_addr, (char *)&this->_hints.sin_addr.s_addr, this->_server->h_length);
	this->_hints.sin_port = htons(iPort);
	if (_udp == false)
		if (connect(this->_connectSocket,(struct sockaddr *) &this->_hints,sizeof(this->_hints)) < 0)
	    {
			std::cerr << "ERROR connecting" << std::endl;
			return false;
	    }
	return true;
}


bool WSocket::connectFromAcceptedFd(void * fd)
{
	SOCKET * sock = static_cast<SOCKET *>(fd);

	if (_udp == true)
    {
		this->_connectSocket = *sock;
		this->_WSAClose = false;
		return true;
    }
	this->_connectSocket = *sock;
	this->_WSAClose = false;
	return true;
}

int WSocket::recv(void ** header, void ** data)
{
	int	ret;

	if (_udp == false)
    {
		*header = new int[2];
		if ((ret = ::recv(this->_connectSocket, (char*)(*header), 2 * sizeof(int), 0)) <= 0)
		return ret;
		*data = new char[((int *)(*header))[1]];
		memset(*data, 0, ((int *)(*header))[1]);
		if ((ret = ::recv(this->_connectSocket, (char*)(*data), ((int *)(*header))[1], 0)) <= 0)
			return ret;
		return 1;
	}
	socklen_t tosize = sizeof(_hints);

	*data = new char[((int *)(*header))[1]];
	memset(*data, 0, ((int *)(*header))[1]);
	if ((ret = ::recvfrom(this->_connectSocket, (char *)(*data), ((int *)(*header))[1], 0, (struct sockaddr *)&_hints, &tosize)) <= 0)
		return ret;
	_host = inet_ntoa(_hints.sin_addr);
	return 1;
}

int WSocket::sendv(int const & size, void * const & data)
{
	if (_udp == false)
		return send(this->_connectSocket, (char*)data, size, NULL);
	else
		return ::sendto(this->_connectSocket, ((char*)data), size, 0, (struct sockaddr *)&this->_hints, sizeof(this->_hints));
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
	return rc;
}

WSocket::~WSocket()
{
	closesocket(this->_connectSocket);

	//Connect from accepted fd
	if (this->_WSAClose == true)
	{
		WSACleanup();
		//freeaddrinfo(this->_results);
	}
}
