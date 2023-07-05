/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** free_memory
*/

#include "server.h"

void free_map(game_t *game)
{
    for (size_t i = 0; i < game->width; i++)
        for (size_t j = 0; j < game->height; j++)
            free(game->map[i][j].ressources);
    for (size_t i = 0; i < game->width; i++)
        free(game->map[i]);
    free(game->map);
}

void free_queue(player_t *queue)
{
    while (queue->next != NULL) {
        queue->next = queue->next->next;
        free(queue->next);
    }
    free(queue);
}

void free_memory(server_t *server)
{
    free_map(server->game);
    free_queue(server->queue);
    free(server);
}
