 #pragma once 

#include "Drawable.h" 
#include "../../protocol.h" 

#include <SFML/Network.hpp>

 #include <string.h> 
 #include <list>
#include <exception>

 class Network 
 { 
 public: 
 	Network(const std::string& host, int portTCP, int portUDP);
 	~Network(void);

 	//udp communication 
 	Protocol::drawable GetPieceWorld(bool&);

 	//tcp communication */
 	Protocol::reponse_type				Register(std::string name, std::string pwd) const; 
 	Protocol::reponse_type				Login(std::string name, std::string pwd) const;
	Protocol::reponse_type				Create();
 	Protocol::reponse_type				Join(int id);
 	std::list<Protocol::party>			GetGameList() const; 
	void								Move(Protocol::cmd_client*) const; 
 	void								Fire() const; 

 private: 
 	// TODO: ajouter class Isocket une fois qu'elle seras au bon endroit 
	std::string     host;
	int			    portUDP;
	int				portTCP;
	sf::TcpSocket*	 socketTCP;
	sf::UdpSocket*	 socketUDP;
	sf::UdpSocket*	 socketUDPRead;
 }; 

