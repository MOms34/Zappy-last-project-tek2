/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myftp-gaetan.darrort [WSL : Ubuntu]
** File description:
** request
*/

#include "server.h"

void request_error_handling(char *buffer)
{
    if (strlen(buffer) < 11)
        printf("Invalid request\n");
}

/// @brief traitement de la requête du client
/// @param server
/// @param buffer donnée reçu du client
/// @param player
void handle_request(server_t *server, char *buffer, player_t *player)
{
    if (strcmp(player->team->name, "GRAPHIC") == 0)
        handle_gui_request(server, buffer, player);
    else
        freeze_action(server->game, player, detect_command(buffer), buffer);
}

void *parse_request(server_t *server, char *buffer, player_t *player)
{
    if (buffer == NULL || strlen(buffer) == 0 ||
    player == NULL)
        return NULL;
    if (player->connected == false)
        handle_not_connected_request(server, buffer, player);
    else if (player->connected == true &&
    server->game->running == true)
        handle_request(server, buffer, player);
    else
        send(player->socket, "ko\n", 3, 0);
    return NULL;
}
