##
## Makefile for  in /home/leurqu_m//Documents/tek3/rtype
## 
## Made by mathieu leurquin
## Login   <leurqu_m@epitech.net>
## 
## Started on  Tue Jan  1 17:03:48 2013 mathieu leurquin
## Last update Tue Jan  8 12:41:54 2013 mathieu leurquin
##


SRC_SR	=	IAUnit.cpp 				\
		HumainUnit.cpp				\
		BasicWeapon.cpp				\
		LifePowerUp.cpp				\
		MovingObstacle.cpp			\
		Obstacle.cpp				\
		Player.cpp				\
		RectangleCollisionDefinition.cpp	\
		Unit.cpp				\
		Game.cpp				\
		Bullet.cpp				\
		CommandManager.cpp

NAME_SR =	server

OBJ_SR	=	$(SRC_SR:.cpp=.o)

CXXFLAGS=	-W -Wall -Wextra -g

CC	=	g++

all		:	$(NAME_SR)

$(NAME_SR)	:	$(OBJ_SR)
			$(CC) $(OBJ_SR) -o $(NAME_SR)

clean		:
			rm -f $(OBJ_SR)

fclean		:	clean
			rm -f $(NAME_SR)

re		:	fclean all
