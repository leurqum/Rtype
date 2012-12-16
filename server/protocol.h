/*
** protocol.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
** 
** Made by marche_m (Maxime Marchès)
** Login   <marche_m@epitech.net>
** 
** Started on  Sun Dec 16 16:18:13 2012 marche_m (Maxime Marchès)
// Last update Sun Dec 16 16:32:45 2012 marche_m (Maxime Marchès)
*/

#ifndef __PROTOCOOL__
# define __PROTOCOOL__

#include <utility>

typedef struct
{
  int	id;
  int	size;
}	package;

typedef	struct
{
  int	nb_monstre;
  int	nb_obstacle;
  int	nb_ship;
}	 monde_param;

typedef	struct
{
  int				id;
  int				type;
  std::pair<float x, float y>	position;
}	drawable;

typedef	struct
{
  int	id;
}	player;


//------------------------------------------------


typedef	struct
{
  int	nb_parties;
}	parties;

typedef	struct
{
  char	* partyName;
  int	nb_players;
}	party;


//------------------------------------------------


typedef struct
{
  int	response;
}	response;


//------------------------------------------------


typedef	struct
{
  std::pair<float x, float y>	velocity
}	move;

typedef	struct
{
  char	* login;
  char	* passwd;
}	create_account;

typedef	struct
{
  char	* login;
  char	* passwd;
}	login;

typedef	struct
{
  char	* party_name;
}	join_game;

typedef	struct
{
  char	* party_name;
}	create_party;



#endif	// __PROTOCOOL__
