/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** not_connect
*/

#include "server.h"

void handle_graphic_connection(server_t *server, player_t *player, team_t *team)
{
    char *map_size = "msz ";
    player_t *new_player = malloc(sizeof(player_t));

    map_size = my_strcat(my_strcat(map_size,
    my_itoa(server->game->width)), " ");
    map_size = my_strcat(my_strcat(map_size, my_itoa(server->game->height)),
    "\n");
    memcpy(new_player, player, sizeof(player_t));
    new_player->next = NULL;
    new_player->team = team;
    new_player->buffer = NULL;
    create_player_back(&team->players, new_player);
    new_player->connected = true;
    send(new_player->socket, map_size, strlen(map_size), 0);
    send(new_player->socket, my_strcat(my_strcat("sgt ",
    my_itoa(server->game->freq)), "\n"),
    strlen(my_itoa(server->game->freq)) + 5, 0);
    get_map(server, new_player);
    get_name(server, new_player);
    team->slots--;
}

void handle_ia_connection(server_t *server, player_t *player, team_t *team)
{
    char *map_size = my_strcat(my_itoa(server->game->width), " ");
    player_t *new_player = malloc(sizeof(player_t));

    map_size = my_strcat(map_size, my_itoa(server->game->height));
    map_size = my_strcat(map_size, "\n");
    memcpy(new_player, player, sizeof(player_t));
    new_player->next = NULL;
    new_player->team = team;
    new_player->buffer = NULL;
    create_player_back(&team->players, new_player);
    new_player->connected = true;
    send(new_player->socket, my_strcat(my_itoa(team->slots), "\n"), strlen(my_itoa(team->slots)) + 1, 0);
    send(new_player->socket, map_size, strlen(map_size), 0);
    spawn_player(server->game, new_player);
    pnw_new_player(server->game, new_player);
    team->slots--;
}

/// @brief ajoute le joueur à la team et lui envoie les dimensions de la map
/// @param server
/// @param buffer
/// @param player
void handle_not_connected_request(server_t *server, char *buffer, player_t *player)
{
    team_t *team = get_team_at_name(server->game->teams, buffer);

    if (team != NULL) {
        if (strcmp(team->name, "GRAPHIC") == 0) {
            handle_graphic_connection(server, player, team);
        } else if (team->slots > 0) {
            handle_ia_connection(server, player, team);
        } else
            send(player->socket, "ko\n", 3, 0);
    } else {
        send(player->socket, "ko\n", 3, 0);
    }
}
