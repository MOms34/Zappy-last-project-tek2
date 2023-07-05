/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** server
*/

#include "server.h"

void error_handling(int ac)
{
    if (ac < 2) {
        printf("Usage : ./myftp port\n");
        exit(84);
    }
}

/// @brief initialise le tableau de pointeur sur structure tile_s
/// @param game
void init_map(game_t *game)
{
    game->map = malloc(sizeof(struct tile_s *) * (game->width));
    for (size_t i = 0; i < game->width; i++) {
        game->map[i] = malloc(sizeof(struct tile_s) * (game->height));
        for (size_t j = 0; j < game->height; j++) {
            game->map[i][j].ressources = malloc(sizeof(int) * 7);
            game->map[i][j].ressources[FOOD] = 0;
            game->map[i][j].ressources[LINEMATE] = 0;
            game->map[i][j].ressources[DERAUMERE] = 0;
            game->map[i][j].ressources[SIBUR] = 0;
            game->map[i][j].ressources[MENDIANE] = 0;
            game->map[i][j].ressources[PHIRAS] = 0;
            game->map[i][j].ressources[THYSTAME] = 0;
            game->map[i][j].players = NULL;
            game->map[i][j].eggs = NULL;
        }
    }
}

/// @brief définie les paramètres par défault du serveur
/// @param server
void set_default_parameters(server_t *server)
{
    struct game_s *game = malloc(sizeof(struct game_s));
    struct team_s *team = malloc(sizeof(struct team_s));

    team->name = "GRAPHIC";
    team->slots = 4;
    team->next = NULL;
    team->players = NULL;
    team->eggs = NULL;
    team->eggs_nb = 0;
    game->freq = 100.0;
    game->width = 10;
    game->height = 10;
    game->clientsNb = 4;
    game->running = true;
    game->id_count = 0;
    game->resources_clock = 0;
    server->port = 4242;
    team->eggs = NULL;
    game->teams = team;
    game->cpt = 0;
    server->game = game;
    server->queue = NULL;
    server->total_resources = malloc(sizeof(int) * 7);
}

void create_server(int ac, char **av, server_t *server)
{
    error_handling(ac);
    set_default_parameters(server);
    parse_arguments(ac, av, server);
    memset(server->client_socket, 0, sizeof(server->client_socket));
    create_socket(server);
    bind_socket(server);
    listen_socket(server);
    init_map(server->game);
}

int main(int ac, char *av[])
{
    struct server_s *server = malloc(sizeof(struct server_s));
    fd_set read_fds;

    (void)read_fds;
    create_server(ac, av, server);
    manage_connection(server);
    free_memory(server);
    return 0;
}

