/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_eject
*/

#include "server.h"

void eject_north(game_t *game, player_t *player, tile_t *tile)
{
    player_t *list = tile->players;

    while (list) {
        if (list->socket != player->socket) {
            delete_player_from_tile(tile, list);
            move_north(game, list);
            send(list->socket, "eject:1\n", 8, 0);
        }
        list = list->next;
    }
}

void eject_south(game_t *game, player_t *player, tile_t *tile)
{
    player_t *list = tile->players;

    while (list) {
        if (list->socket != player->socket) {
            delete_player_from_tile(tile, list);
            move_south(game, list);
            send(list->socket, "eject:2\n", 8, 0);
        }
        list = list->next;
    }
}

void eject_east(game_t *game, player_t *player, tile_t *tile)
{
    player_t *list = tile->players;

    while (list) {
        if (list->socket != player->socket) {
            delete_player_from_tile(tile, list);
            move_east(game, list);
            send(list->socket, "eject:3\n", 8, 0);
        }
        list = list->next;
    }
}

void action_eject_2(game_t *game, player_t *player, tile_t *tile)
{
    if (player->orientation == NORTH)
        eject_north(game, player, tile);
    if (player->orientation == SOUTH)
        eject_south(game, player, tile);
    if (player->orientation == EAST)
        eject_east(game, player, tile);
    if (player->orientation == WEST)
        eject_west(game, player, tile);
    send(player->socket, "ok\n", 3, 0);
}

void action_eject(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map, player->pos_x, player->pos_y);
    char *msg = malloc(sizeof(char) * 200);

    player->last_action = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
    if (tile->players->next == NULL) {
        free(msg);
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    if (tile->eggs)
        eject_eggs(game, tile);
    sprintf(msg, "pex %d\n", player->id);
    send_to_all_graphic(game, msg);
    action_eject_2(game, player, tile);
}
