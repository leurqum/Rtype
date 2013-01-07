//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Mon Jan  7 16:18:56 2013 marche_m (Maxime Marchès)
//

#include "USocket.h"
#include "UServerSocket.h"

int	main(int ac, char ** av)
{
  UServerSocket * sock = new UServerSocket();
  if (sock->init("", "4242") == false)
    return 0;
  sock->launch();
  return 0;
}
