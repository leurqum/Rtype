#pragma once


#include "Drawable.h"
#include "../protocol.h"

#include <string.h>
#include <list>

class Network
{
public:
	Network(void);
	~Network(void);

	//udp communication
	std::list<Drawable> GetLastWorld() const;

	//tcp communication
	Protocol::reponse_type				Register(std::string name, std::string pwd) const;
	Protocol::reponse_type				Login(std::string name, std::string pwd) const;
	Protocol::reponse_type				Join(std::string name);
	std::list<Protocol::party>			GetGameList() const;
	void								Move(Protocol::move) const;
	void								Fire() const;

private:
	// TODO: ajouter class Isocket une fois qu'elle seras au bon endroit
	
};

