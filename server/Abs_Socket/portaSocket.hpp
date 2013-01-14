//
// portaSocket.hpp for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
// 
// Made by marche_m (Maxime Marchès)
// Login   <marche_m@epitech.net>
// 
// Started on  Mon Jan 14 09:47:29 2013 marche_m (Maxime Marchès)
// Last update Mon Jan 14 16:11:27 2013 marche_m (Maxime Marchès)
//

#pragma once

#ifdef __unix__

# include "USocket.hpp"
# include "UServerSocket.hpp"

class UServerSocket;
typedef USocket MySocket;
typedef UServerSocket MyServerSocket;

//-------------------

#elif defined _WIN32

# include "WSocket.hpp"
# include "WServerSocket.hpp"

class WServerSocket;
typedef WSocket MySocket;
typedef WServerSocket MyServerSocket;



#endif
