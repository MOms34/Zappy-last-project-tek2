/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** game_engine
*/

#include "server.h"

void game_engine(server_t *server)
{
    generate_resources(server->game);
    check_for_freeze(server->game);
}

void start_game(server_t *server)
{
    spawn_all_players(server->game);
}
