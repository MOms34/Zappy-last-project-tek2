/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_take
*/

#include "server.h"

static void set_take_resources(game_t *game, player_t *player, char *resource)
{
    if (strcmp(resource, "food") == 0) {
        player->take_object = FOOD;
        return;
    }
    if (strcmp(resource, "linemate") == 0) {
        player->take_object = LINEMATE;
        return;
    }
    if (strcmp(resource, "deraumere") == 0) {
        player->take_object = DERAUMERE;
        return;
    }
    if (strcmp(resource, "sibur") == 0) {
        player->take_object = SIBUR;
        return;
    }
    if (strcmp(resource, "mendiane") == 0) {
        player->take_object = MENDIANE;
        return;
    }
    if (strcmp(resource, "phiras") == 0) {
        player->take_object = PHIRAS;
        return;
    }
    if (strcmp(resource, "thystame") == 0) {
        player->take_object = THYSTAME;
        return;
    }
    player->take_object = -1;
}

void take_freeze(game_t *game, player_t *player, char *buffer)
{
    char **cmd = my_str_to_word_array(buffer, " ");
    char *resource = NULL;

    if (cmd[1] == NULL) {
        player->is_freeze = false;
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    resource = cmd[1];
    set_take_resources(game, player, resource);
    if (player->take_object == -1) {
        send(player->socket, "ko\n", 3, 0);
        player->is_freeze = false;
        player->last_action = -1;
        player->freeze_clock = 0;
        return;
    }
    player->is_freeze = true;
    player->freeze_clock = 7;
    player->last_action = TAKE;
}

void action_take(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map, player->pos_x, player->pos_y);
    char *msg = malloc(sizeof(char) * 100);

    msg[0] = '\0';
    if (tile == NULL || player->take_object == -1 || player->last_action != TAKE) {
        player->last_action = -1;
        player->take_object = -1;
        player->freeze_clock = 0;
        player->is_freeze = false;
        send(player->socket, "ko\n", 3, 0);
        free(msg);
        return;
    }
    switch (player->take_object) {
        case FOOD:
            if (tile->ressources[FOOD] > 0) {
                tile->ressources[FOOD]--;
                player->ressources[FOOD]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, FOOD);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case LINEMATE:
            if (tile->ressources[LINEMATE] > 0) {
                tile->ressources[LINEMATE]--;
                player->ressources[LINEMATE]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, LINEMATE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case DERAUMERE:
            if (tile->ressources[DERAUMERE] > 0) {
                tile->ressources[DERAUMERE]--;
                player->ressources[DERAUMERE]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, DERAUMERE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case SIBUR:
            if (tile->ressources[SIBUR] > 0) {
                tile->ressources[SIBUR]--;
                player->ressources[SIBUR]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, SIBUR);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case MENDIANE:
            if (tile->ressources[MENDIANE] > 0) {
                tile->ressources[MENDIANE]--;
                player->ressources[MENDIANE]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, MENDIANE);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case PHIRAS:
            if (tile->ressources[PHIRAS] > 0) {
                tile->ressources[PHIRAS]--;
                player->ressources[PHIRAS]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, PHIRAS);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        case THYSTAME:
            if (tile->ressources[THYSTAME] > 0) {
                tile->ressources[THYSTAME]--;
                player->ressources[THYSTAME]++;
                send(player->socket, "ok\n", 3, 0);
                sprintf(msg, "pgt %d %d\n", player->socket, THYSTAME);
            } else
                send(player->socket, "ko\n", 3, 0);
            break;
        default:
            send(player->socket, "ko\n", 3, 0);
            break;
    }
    if (msg != NULL && msg[0] != '\0') {
        send_to_all_graphic(game, msg);
        send_to_all_graphic(game, format_bct(tile, player->pos_x,player->pos_y));
        send_to_all_graphic(game, format_pin(player));
    }
    player->last_action = -1;
    player->take_object = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
}
