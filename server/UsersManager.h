#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include "ISocket.h"
#include "User.h"

#include "protocol.h"

class UsersManager
{
public:
	UsersManager(std::string const & file);
	UsersManager();
	~UsersManager(void);
	// WTF: s_protocol ? what is it ?
	s_protocol	* executeCmd(s_protocol * package, ISocket * sock);

private:
	// Execution des commandes
	int					connectUser(std::string const & data, ISocket * sock); // doit recevoir ceci : loginSTRING_SEPARATORmotDePasse
	std::string			getStatusOfUser(std::string const & data);
	int					newSubscriber(std::string const & data);

	// Modifications des Users
	int					addUser(User * user);
	int					addUser(std::string const & data);
	int					addContactToUser(std::string const & userName, std::string const & newContact);
	bool				userExist(std::string const & name);
	User				* getUser(std::string const & name);
	User				* getUser(ISocket * const & sock);

	std::list<User *>	_users;
	std::string			_file;
	bool				_writeBDD;
};

