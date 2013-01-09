#include "Network.h"


Network::Network(void)
{
	// TODO: verifier os pour bonne isocket
}


Network::~Network(void)
{
}

std::list<Drawable>					Network::GetLastWorld() const
{
	std::list<Drawable> World;
	// TODO: fill world properly
	return World;
}

	
Protocol::reponse_type				Network::Register(std::string name, std::string pwd) const
{
	Protocol::package			header;
	header.id = Protocol::LOGIN;
	header.size = sizeof(Protocol::login);

	Protocol::login				login;
	strcpy(login.login, name.c_str());
	strcpy(login.passwd, pwd.c_str());

	Protocol::response			rep;
	rep.response = Protocol::OK;

	// send header
	// send login
	// get reponse

	return rep.response;
}

Protocol::reponse_type				Network::Login(std::string name, std::string pwd) const
{
}

Protocol::reponse_type				Network::Join()
{
}

std::list<Protocol::party>			Network::GetGameList() const
{
}

void								Network::Move(Protocol::move) const
{
}

void								Network::Fire() const
{
}