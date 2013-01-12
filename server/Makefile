##
## Makefile for  in /home/leurqu_m//Documents/tek3/rtype
## 
## Made by mathieu leurquin
## Login   <leurqu_m@epitech.net>
## 
## Started on  Tue Jan  1 17:03:48 2013 mathieu leurquin
## Last update Sat Jan 12 10:33:39 2013 mathieu leurquin
##


SRC_SR		=	./src/source/IAUnit.cpp 			\
			./src/source/HumainUnit.cpp			\
			./src/source/BasicWeapon.cpp			\
			./src/source/LifePowerUp.cpp			\
			./src/source/MovingObstacle.cpp			\
			./src/source/Obstacle.cpp			\
			./src/source/Player.cpp				\
			./src/source/RectangleCollisionDefinition.cpp	\
			./src/source/Unit.cpp				\
			./src/source/Game.cpp				\
			./src/source/Bullet.cpp				\
			./src/source/Server.cpp				\
			./src/source/InterpretPackage.cpp		\

SRC_SOCK 	=	./Abs_Socket/UServerSocket.cpp			\
			./Abs_Socket/USocket.cpp			\
			./Abs_Socket/main.cpp

SRC_THREAD 	=	./Abs_Thread_mutex/UMutex.cpp			\
			./Abs_Thread_mutex/UThread.cpp


NAME_SR		=	server

OBJ_SR		=	$(SRC_SR:.cpp=.o)

OBJ_SOCK	=	$(SRC_SOCK:.cpp=.o)

OBJ_THREAD	=	$(SRC_THREAD:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -g


CC	=	g++

LIB	=	-lpthread


all		:	$(NAME_SR)

$(NAME_SR)	:	$(OBJ_SR) $(OBJ_SOCK) $(OBJ_THREAD)
			$(CC) $(OBJ_SR) $(OBJ_SOCK) $(OBJ_THREAD) -o $(NAME_SR) $(LIB)
			$(CC) ./clientTest.cpp ./Abs_Socket/USocket.cpp -o clientTest

clean		:
			rm -f $(OBJ_SR) $(OBJ_SOCK) $(OBJ_THREAD)

fclean		:	clean
			rm -f $(NAME_SR)

re		:	fclean all
