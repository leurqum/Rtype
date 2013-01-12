//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Sat Jan 12 11:25:36 2013 mathieu leurquin
//

// #include "USocket.hpp"
// #include "UServerSocket.hpp"

#include "../src/include/Game.hpp"

int	main(int ac, char ** av)
{
  //Server *s = new Server();
  Game *g = new Game(0);

  g->loop();
  return 0;
}
