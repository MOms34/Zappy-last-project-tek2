##
## EPITECH PROJECT, 2023
## B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
## File description:
## Makefile
##

SERVER	=	SERVER/
GUI	=	GUI/

all: zappy_server zappy_gui

zappy_server:
	@ make -C $(SERVER) -s

zappy_gui:
	@ make -C $(GUI) -s
	@ mv GUI/zappy_gui .

zappy_ai:
	@ make -C $(AI) -s

clean:
	@ make clean -C $(SERVER) -s
	@ make clean -C $(GUI) -s

fclean:
	@ make fclean -C $(SERVER) -s
	@ make clean -C $(GUI) -s
	@ rm -rf zappy_gui
	@ rm -rf GUI/.qmake.stash

re: fclean all

regui:
	@ make clean -C $(GUI) -s
	@ make -C $(GUI) -s
	@ mv GUI/zappy_gui .

.PHONY: all server gui clean fclean re
