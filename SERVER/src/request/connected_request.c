/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** connected_request
*/

#include "server.h"

void handle_gui_request_3(server_t *server, char *buffer,
    player_t *player, int index)
{
    switch (index) {
        case START:
            server->game->running = true;
            break;
        default:
            break;
    }
}

void handle_gui_request_2(server_t *server, char *buffer,
    player_t *player, int index)
{
    switch (index) {
        case MCT:
            get_map(server, player);
            break;
        case TNA:
            get_name(server, player);
            break;
        case PIN:
            get_pin(server, player, buffer);
            break;
        case PPO:
            get_ppo(server, player, buffer);
            break;
        default:
            handle_gui_request_3(server, buffer, player, index);
    }
}

/// @brief traitement des connections de client connecté a une team
/// si la game est en cours
/// @param server
/// @param buffer
/// @param player
void handle_gui_request(server_t *server, char *buffer, player_t *player)
{
    int index = detect_command(buffer);

    switch (index) {
        case -1:
            send(player->socket, "ko\n", 3, 0);
            break;
        case MSZ:
            get_map_size(server, player);
            break;
        case BCT:
            get_tile(server, buffer, player);
            break;
        default:
            handle_gui_request_2(server, buffer, player, index);
    }
}
