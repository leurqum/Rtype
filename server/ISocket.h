#pragma once

#include <string>
#include "protocol.h"

class ISocket
{
public:
	virtual ~ISocket(){};

	// Initialise le socket et connecte a l’hote passe en parametre
	virtual bool		connectToServer(std::string const & host, std::string const & port) = 0;

	//Initialise l’objet autour du socket passe en parametre
	virtual bool		connectFromAcceptedFd(void * fd) = 0;
	virtual int			recv(std::string& buffer, int blocksize) = 0;
	virtual int			recv(s_protocol * package) = 0;
	virtual int			sendv(std::string const & data) = 0;
	virtual int			sendv(void * const & data, int const & size) = 0;
	virtual	int			sendv(s_protocol * const & package) = 0;
};
