#include "Network.h"

Network::Network(const std::string& host, int portTCP, int portUDP) :
	host(host), portUDP(portUDP), portTCP(portTCP)
{
	this->socketTCP = new sf::TcpSocket();
	this->socketUDP = new sf::UdpSocket();

	this->socketTCP->connect(host, portTCP);
	this->socketUDP->bind(portUDP);
	this->socketUDP->setBlocking(false);
}


Network::~Network(void)
{
}


Protocol::drawable					Network::GetPieceWorld(bool& isReceived) const
{
	Protocol::drawable draw;
	sf::Socket::Status status;

	// TODO: fill world properly
	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;
	status = this->socketUDP->receive((void*)&draw, sizeof(Protocol::drawable), received, sender, port);
	if (status == sf::Socket::Status::Done)
		isReceived = true;
	else
		isReceived = false;
	return draw;
}

	
Protocol::reponse_type				Network::Register(std::string name, std::string pwd) const
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::REGISTER;
	header.size = sizeof(Protocol::create_account);
 	Protocol::create_account	reg;
	memcpy(reg.login, name.c_str(), 50);
	memcpy(reg.passwd, pwd.c_str(), 50);

	// send header + reg
	package = new char[sizeof(header) + sizeof(reg)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &reg, sizeof(reg));
	this->socketTCP->send(package, sizeof(header) + sizeof(reg));

	// get reponse
	Protocol::response rep;
	std::size_t received = 0;
	this->socketTCP->receive((void*)&rep, sizeof(rep), received);
	return rep.response;
}

Protocol::reponse_type				Network::Login(std::string name, std::string pwd) const
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::LOGIN;
	header.size = sizeof(Protocol::login);

	Protocol::login				login;
	memcpy(login.login, name.c_str(), 50);
	memcpy(login.passwd, pwd.c_str(), 50);

	// send header + login
	package = new char[sizeof(header) + sizeof(login)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &login, sizeof(login));
	this->socketTCP->send(package, sizeof(header) + sizeof(login));

	// get reponse
	Protocol::response rep;
	std::size_t received = 0;
	this->socketTCP->receive((void*)&rep, sizeof(rep), received);
	return rep.response;
}

Protocol::reponse_type				Network::Create()
{
	Protocol::package			header;
	header.id = Protocol::CREATE_GAME;
	header.size = 0;

	// send header
	this->socketTCP->send(&header, sizeof(header));

	// get reponse
	Protocol::response rep;
	std::size_t received = 0;
	this->socketTCP->receive((void*)&rep, sizeof(rep), received);
	return rep.response;
}

Protocol::reponse_type				Network::Join(int id)
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::JOIN_GAME;
	header.size = sizeof(Protocol::join_game);
	Protocol::join_game				game;
	game.id = id;

	// send header + party_name
	package = new char[sizeof(header) + sizeof(game)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &game, sizeof(game));
	this->socketTCP->send(package, sizeof(header) + sizeof(game));

	// get reponse
	Protocol::response rep;
	std::size_t received = 0;
	this->socketTCP->receive((void*)&rep, sizeof(rep), received);
	return rep.response;
}

std::list<Protocol::party>			Network::GetGameList() const
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::GET_GAME_LIST;
	header.size = 0;

	//Protocol::response			rep;
	std::list<Protocol::party> partys;

	// send header
	package = new char[sizeof(header)];
	memcpy(package, &header, sizeof(header));
	this->socketTCP->send(package, sizeof(header));

	// get reponse
	void*	game_list;
	std::size_t received = 0;
	//this->socketTCP->receive(game_list, sizeof(rep), received);
	//rep = *(Protocol::response*)data_reponse;
	//header_reponse =  (Protocol::response)(header_reponse);
	//for (int i = 0; i < )
	//{
	//}

	return partys;
}

void								Network::Move(Protocol::cmd_client *cmd) const
{
	this->socketUDP->send(cmd, sizeof(Protocol::cmd_client) + 1, this->host, this->portUDP);
}

void								Network::Fire() const
{
	Protocol::cmd_client* cmd = new Protocol::cmd_client();

	cmd->down = false;
	cmd->top = false;
	cmd->left = false;
	cmd->right = false;
	cmd->fire = true;

	this->socketUDP->send(cmd, sizeof(Protocol::cmd_client) + 1, this->host, this->portUDP);
	delete cmd;
}
