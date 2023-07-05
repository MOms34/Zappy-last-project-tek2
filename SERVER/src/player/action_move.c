/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_move
*/

#include "server.h"

void move_north(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * (1000));

    if (player->pos_y + 1 >= (int)game->height)
        player->pos_y = 0;
    else
        player->pos_y += 1;
    create_player_back(&get_tile_by_pos(game->map,
    player->pos_x, player->pos_y)->players, player);
    sprintf(msg, "ppo %d %d %d %d\n", player->socket, player->pos_x,
        player->pos_y, player->orientation);
    send_to_all_graphic(game, msg);
}

void move_south(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * (1000));

    if (player->pos_y - 1 < 0)
        player->pos_y = (int)game->height - 1;
    else
        player->pos_y -= 1;
    create_player_back(&get_tile_by_pos(game->map,
    player->pos_x, player->pos_y)->players, player);
    sprintf(msg, "ppo %d %d %d %d\n", player->socket, player->pos_x,
        player->pos_y, player->orientation);
    send_to_all_graphic(game, msg);
}

void move_east(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * (1000));

    if (player->pos_x + 1 >= (int)game->width)
        player->pos_x = 0;
    else
        player->pos_x += 1;
    create_player_back(&get_tile_by_pos(game->map,
    player->pos_x, player->pos_y)->players, player);
    sprintf(msg, "ppo %d %d %d %d\n", player->socket, player->pos_x,
        player->pos_y, player->orientation);
    send_to_all_graphic(game, msg);
}

void move_west(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * (1000));

    if (player->pos_x - 1 < 0)
        player->pos_x = (int)game->width - 1;
    else
        player->pos_x -= 1;
    create_player_back(&get_tile_by_pos(game->map,
    player->pos_x, player->pos_y)->players, player);
    sprintf(msg, "ppo %d %d %d %d\n", player->socket, player->pos_x,
        player->pos_y, player->orientation);
    send_to_all_graphic(game, msg);
}

void action_forward(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map, player->pos_x, player->pos_y);

    delete_player_from_tile(tile, player);
    if (player->orientation == NORTH)
        move_north(game, player);
    if (player->orientation == SOUTH)
        move_south(game, player);
    if (player->orientation == EAST)
        move_east(game, player);
    if (player->orientation == WEST)
        move_west(game, player);
    player->last_action = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
    send(player->socket, "ok\n", 3, 0);
}
