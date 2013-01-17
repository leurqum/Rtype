//
// main.cpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Thu Dec 13 10:51:49 2012 marche_m (Maxime Marchès)
// Last update Mon Jan 14 10:45:56 2013 marche_m (Maxime Marchès)
//

#include "../src/include/Server.hpp"

int	main(int ac, char ** av)
{
	if (ac != 2)
	{
		std::cerr << "USAGE: " << av[0] << " PORT" << std::endl;
		return 0;
	}

  Server *s = new Server(av[1]);
  return 1;
}
