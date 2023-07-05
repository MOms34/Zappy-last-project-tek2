##
## EPITECH PROJECT, 2022
## CPP Pool 2023
## File description:
## Makefile
##

CC		=	gcc

CFLAGS	=	-g3 -W -Wall -Wextra -I../../include/server

SRC		=	$(wildcard *.c) \
			$(wildcard ../../lib/server/*.c) \
			$(wildcard linked_list/*.c) \
			$(wildcard free/*.c) \
			$(wildcard request/*.c) \
			$(wildcard request/command/*.c) \
			$(wildcard getters/*.c) \
			$(wildcard player/*.c) \
			$(wildcard game/*.c) \

OBJ		=	$(SRC:.c=.o)

TARGET	=	zappy_server

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	mv $(TARGET) ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../../$(TARGET)
	rm -f a.out

re: fclean all
