##
## Makefile for  in /home/leurqu_m//Documents/tek3/rtype
## 
## Made by mathieu leurquin
## Login   <leurqu_m@epitech.net>
## 
## Started on  Tue Jan  1 17:03:48 2013 mathieu leurquin
## Last update Fri Jan 18 15:44:55 2013 mathieu leurquin
##


NAME		=	./lib/ia.so

CC		=	g++

CXXFLAGS	=	-W -Wall -fPIC

SRC		=	./source/Ia.cpp

OBJ		=	$(SRC:.cpp=.o)


LIB		=	-L/usr/lib -ldl

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LIB) -shared

clean		:
			rm -rf *~ *# $(OBJ)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all