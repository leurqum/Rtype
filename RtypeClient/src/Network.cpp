#include "Network.h"

Network::Network(const std::string& host, const std::string& port)
{
	this->socketTCP = new MySocket();
	this->socketTCP->connectToServer(host, port);

	this->socketUDP = new MySocket();
	this->socketUDP->setUDP(true);
	this->socketUDP->connectToServer(host, port);
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
	void*						package;
	Protocol::package			header;
	header.id = Protocol::REGISTER;
	header.size = sizeof(Protocol::create_account);
 	Protocol::create_account	reg;
	memcpy(reg.login, name.c_str(), 50);
	memcpy(reg.passwd, pwd.c_str(), 50);

	Protocol::response			rep;

	// send header + reg
	package = new char[sizeof(header) + sizeof(reg)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &reg, sizeof(reg));
	this->socketTCP->sendv(sizeof(header) + sizeof(reg), package);

	// get reponse
	void*			header_reponse;
	void*			data_reponse;
	this->socketTCP->recv(&header_reponse, &data_reponse);
	rep = *(Protocol::response*)data_reponse;

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

	Protocol::response			rep;

	// send header + login
	package = new char[sizeof(header) + sizeof(login)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &login, sizeof(login));
	this->socketTCP->sendv(sizeof(header) + sizeof(login), package);

	// get reponse
	void*			header_reponse;
	void*			data_reponse;
	this->socketTCP->recv(&header_reponse, &data_reponse);
	rep = *(Protocol::response*)data_reponse;
	return rep.response;
}

Protocol::reponse_type				Network::Create()
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::CREATE_GAME;
	header.size = 0;
	Protocol::response			rep;

	// send header
	package = new char[sizeof(header)];
	memcpy(package, &header, sizeof(header));
	this->socketTCP->sendv(sizeof(header), package);


	// get reponse
	void*			header_reponse;
	void*			data_reponse;
	this->socketTCP->recv(&header_reponse, &data_reponse);
	rep = *(Protocol::response*)data_reponse;
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
	Protocol::response			rep;

	// send header + party_name
	package = new char[sizeof(header) + sizeof(game)];
	memcpy(package, &header, sizeof(header));
	memcpy((&package + sizeof(header)), &game, sizeof(game));
	this->socketTCP->sendv(sizeof(header) + sizeof(game), package);

	// get reponse
	void*			header_reponse;
	void*			data_reponse;
	this->socketTCP->recv(&header_reponse, &data_reponse);
	rep = *(Protocol::response*)data_reponse;
	return rep.response;
}

std::list<Protocol::party>			Network::GetGameList() const
{
	Protocol::package			header;
	header.id = Protocol::GET_GAME_LIST;
	header.size = 0;

	Protocol::response			rep;

	std::list<Protocol::party> partys;
	// send header

	// get reponse
	void*			header_reponse;
	void*			data_reponse;
	this->socketTCP->recv(&header_reponse, &data_reponse);
	rep = *(Protocol::response*)data_reponse;
	return partys;
}

void								Network::Move(Protocol::cmd_client move) const
{
}

void								Network::Fire() const
{
}
