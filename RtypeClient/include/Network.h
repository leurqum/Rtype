 #pragma once 

#include "Drawable.h" 
#include "../../protocol.h" 

#ifdef __unix__

#include "../../server/Abs_Socket/USocket.hpp"
typedef USocket MySocket;

#elif _WIN32

#include "../../server/Abs_Socket/WSocket.hpp"
typedef WSocket MySocket;

#endif // __unix__

 #include <string.h> 
 #include <list> 

 class Network 
 { 
 public: 
 	Network(const std::string& host, const std::string& port); 
 	~Network(void); 

 	//udp communication 
 	Protocol::drawable GetPieceWorld() const; 

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
	 ISocket*			socketTCP;
	 ISocket*			socketUDP;
 }; 

