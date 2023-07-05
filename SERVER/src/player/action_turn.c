/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_turn
*/

#include "server.h"

void action_turn(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * 1000);

    if (player->last_action == LEFT)
        player->orientation--;
    else
        player->orientation++;
    if (player->orientation > 4)
        player->orientation = 1;
    if (player->orientation < 1)
        player->orientation = 4;
    player->last_action = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
    sprintf(msg, "ppo %d %d %d %d\n", player->socket, player->pos_x,
        player->pos_y, player->orientation);
    send_to_all_graphic(game, msg);
    send(player->socket, "ok\n", 3, 0);
}
