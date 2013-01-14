#pragma once

#include <iostream>
#include <string>
#include "ISocket.hpp"

class IServerSocket
{
public:
	virtual				~IServerSocket() {};
	virtual bool		init(std::string const & listenHost, std::string const & listenPort) = 0;
	virtual ISocket		* myaccept(void * sockType) = 0;
	virtual void		launch() = 0;
};


