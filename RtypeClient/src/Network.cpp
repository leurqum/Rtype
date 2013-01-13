// #include "Network.h"


// Network::Network(void)
// {
// 	// TODO: verifier os pour bonne isocket
// }


// Network::~Network(void)
// {
// }


// std::list<Drawable>					Network::GetLastWorld() const
// {
// 	std::list<Drawable> World;
// 	// TODO: fill world properly
// 	return World;
// }

	
// Protocol::reponse_type				Network::Register(std::string name, std::string pwd) const
// {
// 	Protocol::package			header;
// 	header.id = Protocol::REGISTER;
// 	header.size = sizeof(Protocol::create_account);

// 	Protocol::create_account	reg;
// 	memcpy(reg.login, name.c_str(), 50);
// 	memcpy(reg.passwd, pwd.c_str(), 50);

// 	Protocol::response			rep;
// 	rep.response = Protocol::OK;

// 	// send header + reg

// 	// get reponse

// 	return rep.response;
// }

// Protocol::reponse_type				Network::Login(std::string name, std::string pwd) const
// {
// 	Protocol::package			header;
// 	header.id = Protocol::LOGIN;
// 	header.size = sizeof(Protocol::login);

// 	Protocol::login				login;
// 	memcpy(login.login, name.c_str(), 50);
// 	memcpy(login.passwd, pwd.c_str(), 50);

// 	Protocol::response			rep;
// 	rep.response = Protocol::OK;

// 	// send header + login

// 	// get reponse

// 	return rep.response;
// }

// Protocol::reponse_type				Network::Join(std::string name)
// {
// 	Protocol::package			header;
// 	header.id = Protocol::JOIN_GAME;
// 	header.size = sizeof(Protocol::join_game);

// 	Protocol::join_game				game;
// 	memcpy(game.party_name, name.c_str(), 50);

// 	Protocol::response			rep;
// 	rep.response = Protocol::OK;

// 	// send header + party_name

// 	// get reponse

// 	return rep.response;
// }

// std::list<Protocol::party>			Network::GetGameList() const
// {
// 	Protocol::package			header;
// 	header.id = Protocol::GET_GAME_LIST;
// 	header.size = 0;

// 	Protocol::response			rep;
// 	rep.response = Protocol::OK;

// 	std::list<Protocol::party> partys;

// 	// send header

// 	// get reponse

// 	return partys;
// }

// void								Network::Move(Protocol::move) const
// {
// }

// void								Network::Fire() const
// {
// }
