#include "Network.h"

Network::Network(const std::string& host, int portTCP, int portUDP) :
	host(host), portUDP(portUDP), portTCP(portTCP)
{
	this->socketTCP = new sf::TcpSocket();
	this->socketUDP = new sf::UdpSocket();

	sf::Socket::Status status = this->socketTCP->connect(host, portTCP);
	if (status != sf::Socket::Done)
	  throw std::exception();

	if (this->socketUDP->bind(portUDP) != sf::Socket::Status::Done)
	  std::cout << "fail bind on port (writing)" << std::endl;
	else
	  std::cout << "success bind (writing)" << std::endl;
	this->socketUDP->setBlocking(false);

	
	this->socketUDPRead = new sf::UdpSocket();
	this->socketUDPRead->setBlocking(false);
	if (this->socketUDPRead->bind(4246) != sf::Socket::Status::Done)
	  std::cout << "fail bind on port (reading)" << std::endl;
	else
	  std::cout << "success bind (reading)" << std::endl;
}


Network::~Network(void)
{
}


Protocol::drawable					Network::GetPieceWorld(bool& isReceived)
{
	Protocol::drawable draw;
	memset(&draw, 0, sizeof(draw));
	sf::Socket::Status status;

	// TODO: fill world properly
	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;
	status = this->socketUDPRead->receive((void*)&draw, sizeof(Protocol::drawable), received, sender, port);
	// std::cout << "pos x : " << draw.xPosition << " pos y : " <<  draw.yPosition << std::endl;
	// if (status != sf::Socket::Status::Done)
	//   std::cout << "socket fail" << std::endl;
	if (received != 0)
	  isReceived = true;
	else
	  isReceived = false;
	// std::cout << "isReceived: " << isReceived << " " << received << std::endl; 
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

std::list<Protocol::party*>			Network::GetGameList() const
{
	void*						package;
	Protocol::package			header;
	header.id = Protocol::GET_GAME_LIST;
	header.size = 0;

	//Protocol::response			rep;
	std::list<Protocol::party*> partys;

	// send header
	package = new char[sizeof(header)];
	memcpy(package, &header, sizeof(header));
	this->socketTCP->send(package, sizeof(header));

	// get reponse
	void*			data;
	std::size_t		received;
	this->socketTCP->receive(data, 1024, received);
	// get header;
	Protocol::response* rep = (Protocol::response*)data;
	data = &data + sizeof(Protocol::response);
	Protocol::parties* nb_partie = (Protocol::parties*)(data);
	data = &data + sizeof(Protocol::parties);
	if (rep->response == Protocol::VALIDE)
	{
		for (int i = 0; i < nb_partie->nb_parties; i++)
		{
			Protocol::party* temp = new Protocol::party;;
			temp = (Protocol::party*)&data;
			partys.push_back(temp);
			data = &data + sizeof(Protocol::party);
		}
	}

	return partys;
}

void								Network::Move(Protocol::cmd_client *cmd) const
{
  // std::cout << this->host << ";" << this->portUDP << std::endl;
  if (this->socketUDP->send(cmd, sizeof(Protocol::cmd_client), this->host, this->portUDP) != sf::Socket::Status::Done)
    std::cout << "fail send move" << std::endl;
  // else
  //   std::cout << "send move" << std::endl;
}

void								Network::Fire() const
{
	Protocol::cmd_client* cmd = new Protocol::cmd_client();

	cmd->down = false;
	cmd->top = false;
	cmd->left = false;
	cmd->right = false;
	cmd->fire = true;

	
	std::cout << this->host << ";" << this->portUDP << std::endl;
	if (this->socketUDP->send(cmd, sizeof(Protocol::cmd_client), this->host, this->portUDP) != sf::Socket::Status::Done)
	std::cout << "fail send fire" << std::endl;
	else
	  std::cout << "send fire" << std::endl;
	delete cmd;
}
