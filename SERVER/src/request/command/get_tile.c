/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** get_tile
*/

#include "server.h"

void format_tile(server_t *server, player_t *player, int x, int y)
{
    char *buffer = malloc(sizeof(char) * 1024);
    tile_t *tile = get_tile_by_pos(server->game->map, x, y);

    if (tile == NULL)
        return;
    sprintf(buffer, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile->ressources[FOOD], tile->ressources[LINEMATE],
    tile->ressources[DERAUMERE], tile->ressources[SIBUR],
    tile->ressources[MENDIANE], tile->ressources[PHIRAS],
    tile->ressources[THYSTAME]);
    send(player->socket, buffer, strlen(buffer), 0);
    free(buffer);
}

static int error(server_t *server, char *buffer, int *x, int *y)
{
    char **args = my_str_to_word_array(buffer, " ");

    for (int i = 0; args[i]; i++)
        args[i] = clear_str(args[i], '\n');
    if (array_len(args) != 3)
        return -1;
    if (str_is_digit(args[1]) == false || str_is_digit(args[2]) == false)
        return -1;
    *x = atoi(args[1]);
    *y = atoi(args[2]);
    if (*x < 0 || *x >= (int)server->game->width || *y < 0 ||
    *y >= (int)server->game->height) {
        return -1;
    }
    return 0;
}

void get_tile(server_t *server, char *buffer, player_t *player)
{
    int x = 0;
    int y = 0;

    if (error(server, buffer, &x, &y) == -1) {
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    format_tile(server, player, x, y);
}

void get_map(server_t *server, player_t *player)
{
    for (int x = 0; x < (int)server->game->width; x++)
        for (int y = 0; y < (int)server->game->height; y++)
            format_tile(server, player, x, y);
}

void get_map_size(server_t *server, player_t *player)
{
    char *buffer = malloc(sizeof(char) * 1024);

    sprintf(buffer, "msz %ld %ld\n", server->game->width, server->game->height);
    send(player->socket, buffer, strlen(buffer), 0);
    free(buffer);
}
