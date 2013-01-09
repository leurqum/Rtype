//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Wed Jan  9 16:47:52 2013 marche_m (Maxime Marchès)
//

#include "USocket.hpp"
#include "UServerSocket.hpp"

int	main(int ac, char ** av)
{
  if (ac != 2)
    {
      std::cerr << "Usage: " << av[0] << " PORT_NB" << std::endl;
      return -1;
    }
  UServerSocket * sock = new UServerSocket();
  //sock->setUDP(true); //Problem avec l'udp ...
  if (sock->init("", av[1]) == false)
    return 0;
  sock->launch();
  return 0;
}
