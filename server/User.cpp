#include "User.h"

std::string const & User::getContacts() const
{
	return _contactsString;
}

void	User::setStatus(std::string const & status)
{
	_status = status;
}

std::string const & User::getStatus() const
{
	return _status;
}

ISocket	* const & User::getSocket() const
{
	return _sock;
}

void	User::setSocket(ISocket * const & socket)
{
	_sock = socket;
}

bool	User::matchPassword(std::string const & pswd) const
{
	if (this->_password == pswd)
		return true;
	return false;
}

void	User::setConnected(bool const & connected)
{
	_connected = connected;
}

bool	const & User::isConnected() const
{
	return _connected;
}

bool	User::addContact(std::string const & name)
{
	for (std::list<std::string>::iterator it = _contactsList.begin(); it != _contactsList.end(); it++)
	{
		if (*it == name)
			return false;
	}
	_contactsList.push_back(name);
	_contactsString += name;
	_contactsString += STRING_SEPARATOR;
	return true;
}

User::User(std::string const & d)
{
	_connected = false;
	_name = "";
	_status = "On Babel, and it rocks !";
	_sock = NULL;
	std::string datas = d;

	_name = datas.substr(0, datas.find_first_of(STRING_SEPARATOR));
	datas = datas.substr(datas.find_first_of(STRING_SEPARATOR) + 1, datas.length());
	_password = datas.substr(0, datas.find_first_of(STRING_SEPARATOR));
	datas = datas.substr(datas.find_first_of(STRING_SEPARATOR) + 1, datas.length());
	_contactsString = datas;
	while (true)
	{
		if (datas.find_first_of(STRING_SEPARATOR) == -1)
			break ;
		std::string tmp = datas.substr(0, datas.find_first_of(STRING_SEPARATOR));
		_contactsList.push_back(tmp);
		datas = datas.substr(datas.find_first_of(STRING_SEPARATOR) + 1, datas.length());
	}
	/*
	std::cout << "----------------------------------" << std::endl;
	std::cout << _name << std::endl;
	std::cout << _password << std::endl;
	for (std::list<std::string>::iterator it = _contactsList.begin(); it != _contactsList.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "----------------------------------" << std::endl;
*/
}


User::~User(void)
{
}

std::string User::toString() const
{
	std::string ret = "";

	ret += _name;
	ret += STRING_SEPARATOR;
	ret += _password;
	ret += STRING_SEPARATOR;
	ret += _contactsString;
	return ret;
}

std::string const & User::getName() const
{
	return _name;
}

std::ostream & operator<<(std::ostream & os, User * user)
{
	std::string tmp = user->toString();
	os << (tmp);
	return os;
}