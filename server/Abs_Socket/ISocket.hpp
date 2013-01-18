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
  virtual int		recv(void ** header, void ** data) = 0;
  virtual int		sendv(std::string const & data) = 0;
  virtual int		sendv(int const & size, void * const & data) = 0;		//TODO
  virtual void		setUDP(bool const & val) = 0;
  virtual bool		isUDP() const = 0;										//TODO
  virtual void		setHost(std::string const & ip) = 0;
  virtual std::string const & getHost() const = 0;							//TODO
};
