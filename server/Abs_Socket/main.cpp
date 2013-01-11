//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Fri Jan 11 19:31:41 2013 mathieu leurquin
//

// #include "USocket.hpp"
// #include "UServerSocket.hpp"

#include "../src/include/Server.hpp"

int	main(int ac, char ** av)
{
  Server *s = new Server();
  // UServerSocket * sock = new UServerSocket();
  // //sock->setUDP(true); //Problem avec l'udp ...
  // if (sock->init("", av[1]) == false)
  //   return 0;
  // sock->launch();
  return 0;
}
