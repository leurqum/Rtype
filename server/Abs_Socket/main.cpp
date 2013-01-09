//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Wed Jan  9 09:55:24 2013 marche_m (Maxime Marchès)
//

#include "USocket.hpp"
#include "UServerSocket.hpp"

int	main(int ac, char ** av)
{
  UServerSocket * sock = new UServerSocket();
  sock->setUDP(true);
  if (sock->init("", "4242") == false)
    return 0;
  sock->launch();
  return 0;
}
