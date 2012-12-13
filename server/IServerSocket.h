#pragma once

#include <iostream>
#include <string>
#include "ISocket.h"
#include "UsersManager.h"

class IServerSocket
{
public:
	virtual				~IServerSocket() {};
	virtual bool		init(std::string const & listenHost, std::string const & listenPort, UsersManager * usersManager) = 0;
	virtual ISocket		* myaccept() = 0;
	virtual void		launch() = 0;
};


