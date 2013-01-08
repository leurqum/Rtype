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
}

	
Protocol::reponse_type				Network::Register(std::string name, std::string pwd) const
{
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