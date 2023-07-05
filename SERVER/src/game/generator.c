/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** generator
*/

#include "server.h"

void spawn_resource(game_t *game, int *stock)
{
    int x = rand() % game->width;
    int y = rand() % game->height;
    int resource = rand() % 7;
    char *msg = malloc(sizeof(char) * 1000);

    while (stock[resource] <= 0)
        resource = rand() % 7;
    stock[resource] -= 1;
    game->map[x][y].ressources[resource] += 1;
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    game->map[x][y].ressources[FOOD], game->map[x][y].ressources[LINEMATE],
    game->map[x][y].ressources[DERAUMERE], game->map[x][y].ressources[SIBUR],
    game->map[x][y].ressources[MENDIANE], game->map[x][y].ressources[PHIRAS],
    game->map[x][y].ressources[THYSTAME]);
    send_to_all_graphic(game, msg);
}

/// @brief parcours la map et ajoute des ressources aléatoirement. NOTE :
/// si il reste des resources après le for, alors je les ajoute à une tile
/// aléatoire de la map jusqu'à ce qu'il n'y ai plus aucun stock
/// @param game
void generate_resources(game_t *game)
{
    int *stock = NULL;

    game->resources_clock -= 1;
    if (game->resources_clock > 0)
        return;
    game->resources_clock = 20;
    stock = calculate_resources_available(game);
    while (stock[FOOD] > 0 || stock[LINEMATE] > 0 || stock[DERAUMERE] > 0 ||
    stock[SIBUR] > 0 || stock[MENDIANE] > 0 || stock[PHIRAS] > 0 ||
    stock[THYSTAME])
        spawn_resource(game, stock);
    free(stock);
}
