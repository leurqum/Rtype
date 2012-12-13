#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <list>

#include "protocol.h"
#include "ISocket.h"

class User
{
public:
	explicit User(std::string const & datas);
	~User(void);
	std::string				toString() const;
	bool					addContact(std::string const & newContact);
	bool const &			isConnected() const;
	bool					matchPassword(std::string const & pswd) const;
	ISocket	* const &		getSocket() const;
	std::string const &		getStatus() const;
	std::string const &		getName() const;
	std::string const &		getContacts() const;
	void					setConnected(bool const & connected);
	void					setSocket(ISocket * const & socket);
	void					setStatus(std::string const & status);

private:
	std::string				_name;
	std::string				_password;
	std::list<std::string>	_contactsList;
	std::string				_contactsString;
	std::string				_status;
	bool					_connected;
	ISocket					* _sock;
};

std::ostream & operator<<(std::ostream & os, User * user);
