/*
** protocol.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
** 
** Made by marche_m (Maxime Marchès)
** Login   <marche_m@epitech.net>
** 
** Started on  Sun Dec 16 16:18:13 2012 marche_m (Maxime Marchès)
** Last update Tue Jan 15 18:03:54 2013 mathieu leurquin
*/

#ifndef __PROTOCOOL__
# define __PROTOCOOL__

#include <utility>

namespace Protocol
{

enum type_cmd
{
	REGISTER,
	LOGIN,
	GET_GAME_LIST,
	GAME_LIST,
	JOIN_GAME,
	CREATE_GAME,
	SEND_WORLD,
	MOVE,
	FIRE,
	RESPONSE
};



typedef struct
{
  int	id;
  int	size;
}	package;

//------------------------------------------------

typedef	struct
{
  int	nb_monstre;
  int	nb_obstacle;
  int	nb_ship;
  int	nb_bullet;
  int	nb_bonus;
}	 monde_param;

enum type_drawable
{
  SHIP,
  ENEMY_EASY,
  ENEMY_HARD,
  BOSS,
  BULLET_LINEAR,
  BULLET_RAYON,
  BONUS,
  OBSTACLE,
  DEAD
};

enum patern_enemie
{
  STATIC,
  SOLO,
  PACKV,
  VFLY,
  LINEUP,
  LINEDOWN
};

#define XMAX 800
#define YMAX 600

typedef	struct
{
  int  id;
  type_drawable  type;
  float  xPosition;
  float  yPosition;
}	drawable;

//------------------------------------------------


typedef	struct
{
  int	nb_parties;
}	parties;

typedef	struct
{
  int	nb_players;
}	party;


//------------------------------------------------

enum reponse_type
{
  VALIDE,
  INVALID_LOGIN,
  INVALID_PASSWORD,
  INVALID_GAME,
  CANT_JOIN_GAME
};

typedef struct
{
  reponse_type	response;
}	response;


//------------------------------------------------


typedef	struct
{
  bool top;
  bool right;
  bool down;
  bool left;
  bool fire;
}	cmd_client;

typedef	struct
{
  char	login[50];
  char	passwd[50];
}	create_account;

typedef	struct
{
  char	login[50];
  char	passwd[50];
}	login;

typedef	struct
{
  int	id;
}	join_game;

/* typedef	struct */
/* { */
/*   char	party_name[50]; */
/* }	create_party; */

typedef struct
{
	int top;
	int left;
	int right;
	int down;
} move;

}

#endif	// __PROTOCOOL__
