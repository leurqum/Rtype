/*
** protocol.h for  in /home/marche_m/workspace/tek3/cpp/r-type/Rtype/server
** 
** Made by marche_m (Maxime Marchès)
** Login   <marche_m@epitech.net>
** 
** Started on  Sun Dec 16 16:18:13 2012 marche_m (Maxime Marchès)
** Last update Sun Dec 30 14:05:39 2012 marche_m (Maxime Marchès)
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
  }	 monde_param;

  enum type_drawable
  {
    SHIP,
    MONSTER, // several monsters ?
    OBSTACLE, // several obstacles ?
    BULLET // no nb_bullet in monde_param, is it considered as obstacle ?
  };

  typedef	struct
  {
    int  id;
    int  type;
    float  xPosition;
    float  yPosition;
  }	drawable;

  /* struct WTF
     typedef	struct
     {
     int	id;
     }	player;
  */

  //------------------------------------------------


  typedef	struct
  {
    int	nb_parties;
  }	parties;

  typedef	struct
  {
    char	partyName[50];
    int	nb_players;
  }	party;


  //------------------------------------------------

  enum reponse_type
  {
    OK,
    INVALID_LOGIN,
    INVALID_PASSWORD,
    INVALID_GAME_NAME,
    CANT_JOIN_GAME
  };

  typedef struct
  {
    int	response;
  }	response;


  //------------------------------------------------


  typedef	struct
  {
    float xVelocity;
    float yVelocity;
  }	move;

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
    char	party_name[50];
  }	join_game;

  typedef	struct
  {
    char	party_name[50];
  }	create_party;

}

#endif	// __PROTOCOOL__
