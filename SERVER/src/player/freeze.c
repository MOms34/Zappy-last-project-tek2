/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** freeze
*/

#include "server.h"

void freeze_action_4(game_t *game, player_t *player, int action)
{
    switch (action) {
        case EJECT:
            player->last_action = EJECT;
            player->freeze_clock = 7;
            break;
        case RIGHT:
            player->last_action = RIGHT;
            player->freeze_clock = 7;
            break;
        default:
            player->freeze_clock = 0;
            player->last_action = 0;
            player->is_freeze = false;
            send(player->socket, "ko\n", 3, 0);
            break;
    }
}

void freeze_action_3(game_t *game, player_t *player, int action)
{
    switch (action) {
        case FORK:
            player->last_action = FORK;
            player->freeze_clock = 42;
            break;
        case FORWARD:
            player->last_action = FORWARD;
            player->freeze_clock = 7;
            break;
        case EJECT:
            player->last_action = EJECT;
            player->freeze_clock = 7;
            break;
        default:
            freeze_action_4(game, player, action);
            break;
    }
}

void freeze_action_2(game_t *game, player_t *player, int action)
{
    switch (action) {
        case INVENTORY:
            player->last_action = INVENTORY;
            player->freeze_clock = 1;
            break;
        case LOOK:
            player->last_action = LOOK;
            player->freeze_clock = 7;
            break;
        case LEFT:
            player->last_action = LEFT;
            player->freeze_clock = 7;
            break;
        default:
            freeze_action_3(game, player, action);
            break;
    }
}

void freeze_action(game_t *game, player_t *player, int action, char *buffer)
{
    if (player->is_freeze == true)
        return;
    player->is_freeze = true;
    switch (action) {
        case INCANTATION:
            incantation_cmd(game, player);
            break;
        case TAKE:
            take_freeze(game, player, buffer);
            break;
        case SET:
            set_freeze(game, player, buffer);
            break;
        case BROADCAST:
            broadcast_freeze(game, player, buffer);
            break;
        default:
            freeze_action_2(game, player, action);
            break;
    }
}
