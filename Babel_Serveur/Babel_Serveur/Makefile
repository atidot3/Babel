##
## Makefile for max in /home/dauver_m/work/bomberman
## 
## Made by dauvergne maxime
## Login   <dauver_m@epitech.net>
## 
## Started on  Fri May  9 11:11:23 2014 dauvergne maxime
## Last update Sun Jun  8 18:05:32 2014 Loïc Echevet
##

CC		=	clang++

RM		=	rm -f

SRC_DIR		=	CPP/

INC_DIR		=	./

OBJ_DIR		=	obj/

FILE		=	Client.cpp \
			FileContact.cpp \
			main.cpp \
			Protocole.cpp \
			Select.cpp \
			Server.cpp


SRC		=	$(addprefix $(SRC_DIR), $(FILE))

NAME		=	server


OBJ	=	 $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))


$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		@mkdir -p $(OBJ_DIR)
		$(CC) -c -o $@ $< -I $(INC_DIR) -g

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

init:
		@mkdir -p $(SRC_DIR)
		@mkdir -p $(OBJ_DIR)