/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** generator_bis
*/

#include "server.h"

static tile_t *find_empty_tile_1(game_t *game, int x)
{
    for (int y = 0; y < (int)game->width; y++)
            if (game->map[x][y].ressources[FOOD] == 0 &&
            game->map[x][y].ressources[LINEMATE] == 0 &&
            game->map[x][y].ressources[DERAUMERE] == 0 &&
            game->map[x][y].ressources[SIBUR] == 0 &&
            game->map[x][y].ressources[MENDIANE] == 0 &&
            game->map[x][y].ressources[PHIRAS] == 0 &&
            game->map[x][y].ressources[THYSTAME] == 0 &&
            game->map[x][y].players == NULL)
                return (&game->map[x][y]);
    return NULL;
}

tile_t *find_empty_tile(game_t *game)
{
    for (int x = 0; x < (int)game->height; x++)
        if (find_empty_tile_1(game, x) != NULL)
            return (find_empty_tile_1(game, x));
    return NULL;
}

int *calculate_resources_available_1(game_t *game, int *stock)
{
    for (int x = 0; x < (int)game->width; x++)
        for (int y = 0; y < (int)game->height; y++) {
            stock[FOOD] -= game->map[x][y].ressources[FOOD];
            stock[LINEMATE] -= game->map[x][y].ressources[LINEMATE];
            stock[DERAUMERE] -= game->map[x][y].ressources[DERAUMERE];
            stock[SIBUR] -= game->map[x][y].ressources[SIBUR];
            stock[MENDIANE] -= game->map[x][y].ressources[MENDIANE];
            stock[PHIRAS] -= game->map[x][y].ressources[PHIRAS];
            stock[THYSTAME] -= game->map[x][y].ressources[THYSTAME];
        }
    return (stock);
}

/// @brief calcule le nombre de ressources disponibles
/// @param game
/// @return
int *calculate_resources_available(game_t *game)
{
    int *stock = malloc(sizeof(int) * 7);
    size_t map_size = 0;

    map_size = game->width * game->height;
    stock[FOOD] = (int)map_size * 0.5;
    stock[LINEMATE] = (int)map_size * 0.3;
    stock[DERAUMERE] = (int)map_size * 0.15;
    stock[SIBUR] = (int)map_size * 0.1;
    stock[MENDIANE] = (int)map_size * 0.1;
    stock[PHIRAS] = (int)map_size * 0.08;
    stock[THYSTAME] = (int)map_size * 0.05;
    stock = calculate_resources_available_1(game, stock);
    return (stock);
}
