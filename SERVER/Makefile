##
## EPITECH PROJECT, 2022
## CPP Pool 2023
## File description:
## Makefile
##

CC		=	gcc

CFLAGS	=	-g3 -W -Wall -Wextra -I./include/

SRC		=	$(wildcard src/*.c) \
			$(wildcard lib/*.c) \
			$(wildcard src/linked_list/*.c) \
			$(wildcard src/free/*.c) \
			$(wildcard src/request/*.c) \
			$(wildcard src/request/command/*.c) \
			$(wildcard src/getters/*.c) \
			$(wildcard src/player/*.c) \
			$(wildcard src/game/*.c) \

OBJ		=	$(SRC:.c=.o)

TARGET	=	zappy_server

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm
	mv $(TARGET) ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(TARGET)
	rm -f a.out

re: fclean all re
