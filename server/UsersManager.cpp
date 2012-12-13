#include "UsersManager.h"

s_protocol		* UsersManager::executeCmd(s_protocol * cmd, ISocket * sock)
{
	s_protocol * ret = new s_protocol;
//	User * curentUser = this->getUser(sock);
	ret->cmdId = cmd->cmdId;

	if (cmd->cmdId == CONNECT)
	{
		std::string data = (char*)(cmd->data);
		int res = this->connectUser(data, sock);
		ret->size = sizeof(int);
		ret->data = new int(res);
		return ret;
	}
	if (cmd->cmdId == GET_STATUS)
	{
		std::string data = (char*)(cmd->data);
		std::string res = this->getStatusOfUser(data);
		ret->size = res.length() + 1;
		ret->data = (void *)res.c_str();
		return ret;
	}
	if (cmd->cmdId == NEW_SUBSCRIBER)
	{
		std::string data = (char*)(cmd->data);
		int res = this->newSubscriber(data);
		ret->size = sizeof(int);
		ret->data = new int(res);
		return ret;
	}
	if (cmd->cmdId == SET_STATUS)
	{
		std::string data = (char*)(cmd->data);
		data = data.substr(0, data.find_first_of(":"));
		User * usr = this->getUser(sock);
		usr->setStatus(data);
		return NULL;
	}
	if (cmd->cmdId == ADD_CONTACT)
	{
		ret->size = sizeof(int);
		std::string data = (char*)(cmd->data);
		User * usr = this->getUser(sock);
		ret->data = new int(this->addContactToUser(usr->getName(), data));
		return ret;
	}
	if (cmd->cmdId == GET_CONTACTS)
	{
		User * usr = this->getUser(sock);
		std::string *tmp = new std::string(usr->getContacts());
		ret->size = tmp->length() + 1;
		ret->data = (void*)tmp->c_str();
		return ret;
	}
	if (cmd->cmdId == START_CALL)
	{
		//TODO
	}
	if (cmd->cmdId == END_CALL)
	{
		//TODO
	}
	return NULL;
}

int		UsersManager::newSubscriber(std::string const & data)
{
	std::string tmpS = data;

	std::string login = tmpS.substr(0, tmpS.find_first_of(":"));
	if (this->userExist(login) == true)
		return 0;
	User * usr = new User(data);
	_users.push_back(usr);
	return 1;
}

std::string			UsersManager::getStatusOfUser(std::string const & data)
{
	std::string login = data.substr(0, data.find_first_of(":"));

	return this->getUser(login)->getStatus();
}

int		UsersManager::connectUser(std::string const & data, ISocket * sock)
{
	std::string tmpS = data;
	int verif = 0;
	for (unsigned int i = 0; i < data.length(); i++)
		if (data[i] == STRING_SEPARATOR)
			verif++;
	if (verif < MIN_NB_SEPARATOR_USER)
		return 2;
	std::string login = tmpS.substr(0, tmpS.find_first_of(":"));
	tmpS = tmpS.substr(tmpS.find_first_of(":") + 1, tmpS.length());
	std::string password = tmpS.substr(0, tmpS.find_first_of(":"));
	if (this->userExist(login) == false)
		return 0;
	User * tmp = this->getUser(login);
	if (tmp->matchPassword(password) == false)
		return 2;
	tmp->setConnected(true);
	tmp->setSocket(sock);
	return 1;
}

int		UsersManager::addContactToUser(std::string const & userName, std::string const & newContact)
{
	User * tmp = this->getUser(userName);

	// see protocol.h for details
	if (tmp == NULL)
	{
		std::cerr << "Login of user invalid" << std::endl;
		return 0;
	}
	if (this->userExist(newContact) == false)
	{
		std::cerr << "new contact login invalid" << std::endl;
		return 2;
	}
	if (tmp->addContact(newContact) == true)
		return 1;
	std::cerr << "contact already in contact list" << std::endl;
	return 3;
}

User	* UsersManager::getUser(std::string const & userName)
{
	for (std::list<User *>::iterator it = _users.begin(); it != _users.end(); it++)
		if ((*it)->getName() == userName)
			return *it;
	return NULL;
}

User	* UsersManager::getUser(ISocket * const & sock)
{
	for (std::list<User *>::iterator it = _users.begin(); it != _users.end(); it++)
		if ((*it)->getSocket() == sock)
			return *it;
	return NULL;
}

int		UsersManager::addUser(User * user)
{
	if (this->userExist(user->getName()) == true)
	{
		std::cerr << "User: already exist" << std::endl;
		return 0;
	}
	_users.push_back(user);
	return 1;
}

int		UsersManager::addUser(std::string const & data)
{
	if (this->userExist(data.substr(0, data.find_first_of(STRING_SEPARATOR))) == true)
	{
		std::cerr << "User: already exist" << std::endl;
		return 0;
	}
	User * newUser = new User(data);
	_users.push_back(newUser);
	return 1;
}

bool	UsersManager::userExist(std::string const & name)
{
	for (std::list<User *>::iterator it = _users.begin(); it != _users.end(); it++)
		if ((*it)->getName() == name)
			return true;
	return false;
}

UsersManager::UsersManager()
{
	_writeBDD = false;
	std::cerr << "Using a factory." << std::endl;
	_users.push_back(new User("root:toor:test:"));
	_users.push_back(new User("test:test:"));
}
UsersManager::UsersManager(std::string const & file)
{
	_writeBDD = true;
	_file = file;
	std::ifstream bdd;

	bdd.open(_file);
	if (bdd.is_open() == false)
	{
		std::cerr << "Error on file: " << file << std::endl;
		std::cerr << "Using a factory." << std::endl;
		_users.push_back(new User("root:toor:test:"));
		_users.push_back(new User("test:test:"));
	}
	else
	{
		std::string data;
		while (!bdd.eof())
		{
			getline(bdd, data);
			int nbSeparator = 0;
			for (unsigned int i = 0; i < data.length(); i++)
				if (data[i] == STRING_SEPARATOR)
				{
					nbSeparator++;
					if (nbSeparator >= MIN_NB_SEPARATOR_USER)
						break ;
				}
			if (nbSeparator >= MIN_NB_SEPARATOR_USER)
				_users.push_back(new User(data));
		}
	}
	bdd.close();
}


UsersManager::~UsersManager(void)
{
	if (_writeBDD == true)
	{
		std::fstream bdd(_file, std::ios::out | std::ios::trunc);
		if (bdd.is_open() == true)
		{
			for (std::list<User *>::iterator it = _users.begin(); it != _users.end();)
			{
				bdd << (*it) << std::endl;
				bdd.flush();
				User * tmp = *it;
				it = _users.erase(it);
				delete tmp;
			}
			bdd.close();
		}
	}
}
