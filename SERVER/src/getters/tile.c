/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** tile
*/

#include "server.h"

char *format_bct(tile_t *tile, int x, int y)
{
    char *msg = malloc(sizeof(char) * 1000);

    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile->ressources[FOOD], tile->ressources[LINEMATE],
    tile->ressources[DERAUMERE], tile->ressources[SIBUR],
    tile->ressources[MENDIANE], tile->ressources[PHIRAS],
    tile->ressources[THYSTAME]);
    return msg;
}

tile_t *get_tile_by_pos(tile_t **map, int x, int y)
{
    tile_t *tile = NULL;

    tile = &map[x][y];
    return tile;
}

int get_nb_players_on_tile(tile_t *tile)
{
    int nb = 0;
    player_t *tmp = NULL;

    tmp = tile->players;
    if (!tmp)
        return 0;
    while (tmp) {
        nb++;
        tmp = tmp->next;
    }
    return nb;
}

player_t **get_players_to_incant(tile_t *tile, player_t *player,
    int nb_players)
{
    player_t **players = malloc(sizeof(player_t *) * (nb_players + 1));
    player_t *tmp = NULL;
    int i = 0;

    tmp = tile->players;
    players[i] = player;
    i++;
    while (tmp) {
        if (tmp->level == player->level && tmp->is_freeze == false &&
        tmp->socket != player->socket) {
            players[i] = tmp;
            i++;
        }
        tmp = tmp->next;
    }
    players[i] = NULL;
    return players;
}

void delete_player_from_tile(tile_t *tile, player_t *player)
{
    player_t *temp = tile->players;
    player_t *prev = NULL;
    int socket = player->socket;

    if (temp != NULL && temp->socket == socket) {
        tile->players = temp->next;
        return;
    }
    while (temp != NULL && temp->socket != socket) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
}
