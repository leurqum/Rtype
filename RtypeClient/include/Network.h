 #pragma once 

#include "Drawable.h" 
#include "../../protocol.h" 
#include "../../server/Abs_Socket/portaSocket.hpp"

 #include <string.h> 
 #include <list> 

 class Network 
 { 
 public: 
 	Network(const std::string& host, const std::string& port); 
 	~Network(void); 

 	//udp communication 
 	std::list<Drawable> GetLastWorld() const; 

 	//tcp communication */
 	Protocol::reponse_type				Register(std::string name, std::string pwd) const; 
 	Protocol::reponse_type				Login(std::string name, std::string pwd) const;
	Protocol::reponse_type				Create();
 	Protocol::reponse_type				Join(int id);
 	std::list<Protocol::party>			GetGameList() const; 
	void								Move(Protocol::cmd_client) const; 
 	void								Fire() const; 

 private: 
 	// TODO: ajouter class Isocket une fois qu'elle seras au bon endroit 
	 ISocket*			socketTCP;
	 ISocket*			socketUDP;
 }; 

