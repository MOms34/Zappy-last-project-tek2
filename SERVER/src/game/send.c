/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** send
*/

#include "server.h"

void send_to_all_players(game_t *game, char *str)
{
    player_t *player = NULL;

    if (game->teams == NULL)
        return;
    if (game->teams->players == NULL)
        return;
    player = game->teams->players;
    while (player) {
        send(player->socket, str, strlen(str), 0);
        player = player->next;
    }
    free(str);
}

void send_to_all_graphic(game_t *game, char *str)
{
    team_t *team = get_team_at_name(game->teams, "GRAPHIC");
    player_t *graphics = NULL;

    if (team == NULL)
        return;
    if (team->players == NULL)
        return;
    graphics = team->players;
    while (graphics) {
        send(graphics->socket, str, strlen(str), 0);
        graphics = graphics->next;
    }
    free(str);
}

char *get_all_graphic(game_t *game, player_t *players)
{
    char *str = malloc(sizeof(char) * 1000);
    str = memset(str, 0, 1000);
    player_t *player = NULL;

    if (game->teams == NULL)
        return NULL;
    if (game->teams->players == NULL)
        return NULL;
    player = game->teams->players;
    while (player) {
        if (player->socket != players->socket) {
            sprintf(str, " %d", player->socket);
        }
        player = player->next;
    }
    if (str == NULL || str[0] == '\0')
        return NULL;
    return str;
}
