/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_set_2
*/

#include "server.h"

void action_set_5(game_t *game, player_t *player, tile_t *tile, char **msg)
{
    switch (player->set_object) {
        case THYSTAME:
            if (player->ressources[THYSTAME] > 0) {
                tile->ressources[THYSTAME]++;
                player->ressources[THYSTAME]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, THYSTAME);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        default:
            send(player->socket, "ko\n", 3, 0);
            break;
    }
}

void action_set_4(game_t *game, player_t *player, tile_t *tile, char **msg)
{
    switch (player->set_object) {
        case MENDIANE:
            if (player->ressources[MENDIANE] > 0) {
                tile->ressources[MENDIANE]++;
                player->ressources[MENDIANE]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, MENDIANE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case PHIRAS:
            if (player->ressources[PHIRAS] > 0) {
                tile->ressources[PHIRAS]++;
                player->ressources[PHIRAS]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, PHIRAS);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        default:
            action_set_5(game, player, tile, msg);
            break;
    }
}

void action_set_3(game_t *game, player_t *player, tile_t *tile, char **msg)
{
    switch (player->set_object) {
        case DERAUMERE:
            if (player->ressources[DERAUMERE] > 0) {
                tile->ressources[DERAUMERE]++;
                player->ressources[DERAUMERE]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, DERAUMERE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case SIBUR:
            if (player->ressources[SIBUR] > 0) {
                tile->ressources[SIBUR]++;
                player->ressources[SIBUR]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, SIBUR);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        default:
            send(player->socket, "ko\n", 3, 0);
            break;
    }
}

void action_set_2(game_t *game, player_t *player, tile_t *tile, char **msg)
{
    switch (player->set_object) {
        case FOOD:
            if (player->ressources[FOOD] > 0) {
                tile->ressources[FOOD]++;
                player->ressources[FOOD]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, FOOD);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case LINEMATE:
            if (player->ressources[LINEMATE] > 0) {
                tile->ressources[LINEMATE]++;
                player->ressources[LINEMATE]--;
                send(player->socket, "ok\n", 3, 0);
                sprintf(*msg, "pdr %d %d\n", player->socket, LINEMATE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        default:
            action_set_3(game, player, tile, msg);
            break;
    }
}
