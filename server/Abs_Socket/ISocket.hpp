#pragma once

#include <string>
//#include "protocol.h"

class ISocket
{
 public:
  virtual ~ISocket(){};

  // Initialise le socket et connecte a l’hote passe en parametre
  virtual bool		connectToServer(std::string const & host, std::string const & port) = 0;

  //Initialise l’objet autour du socket passe en parametre
  virtual bool		connectFromAcceptedFd(void * fd) = 0;
  virtual int		recv() = 0;
  virtual int		sendv(std::string const & data) = 0;
};
