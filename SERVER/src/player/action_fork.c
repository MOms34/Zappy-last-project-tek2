/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_look
*/

#include "server.h"

void action_fork_2(game_t *game, player_t *player, char *msg, egg_t *egg)
{
    sprintf(msg, "enw %d %d %d %d\n", egg->id, player->socket,
        player->pos_x, player->pos_y);
    send_to_all_graphic(game, msg);
    player->last_action = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
}

void action_fork(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * 100);
    char *msg2 = malloc(sizeof(char) * 100);
    egg_t *egg = malloc(sizeof(egg_t));
    tile_t *tile = get_tile_by_pos(game->map, player->pos_x, player->pos_y);

    egg->is_hatched = false;
    egg->id = player->team->eggs_nb;
    egg->time = 0;
    egg->pos_x = player->pos_x;
    egg->pos_y = player->pos_y;
    egg->team = player->team;
    create_egg_back(&tile->eggs, egg);
    create_egg_back(&player->team->eggs, egg);
    send(player->socket, "ok\n", 3, 0);
    sprintf(msg2, "pfk %d\n", player->socket);
    send_to_all_graphic(game, msg2);
    action_fork_2(game, player, msg, egg);
}
