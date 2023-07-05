/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** get_name
*/

#include "server.h"

void get_name(server_t *server, player_t *player)
{
    team_t *team_list = server->game->teams;
    char *response = malloc(sizeof(char) * 1000);

    if (team_list == NULL)
        return;
    while (team_list) {
        if (strcmp(team_list->name, "GRAPHIC") != 0) {
            sprintf(response, "tna %s\n", team_list->name);
            send(player->socket, response, strlen(response), 0);
            memset(response, 0, 1000);
        }
        team_list = team_list->next;
    }
    free(response);
}
