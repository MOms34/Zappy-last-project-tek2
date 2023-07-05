/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_take
*/

#include "server.h"

void set_set_resources_2(game_t *game, player_t *player, char *resource)
{
    if (strcmp(resource, "mendiane") == 0) {
        player->set_object = MENDIANE;
        return;
    }
    if (strcmp(resource, "phiras") == 0) {
        player->set_object = PHIRAS;
        return;
    }
    if (strcmp(resource, "thystame") == 0) {
        player->set_object = THYSTAME;
        return;
    }
    player->set_object = -1;
}

void set_set_resources(game_t *game, player_t *player, char *resource)
{
    if (strcmp(resource, "food") == 0) {
        player->set_object = FOOD;
        return;
    }
    if (strcmp(resource, "linemate") == 0) {
        player->set_object = LINEMATE;
        return;
    }
    if (strcmp(resource, "deraumere") == 0) {
        player->set_object = DERAUMERE;
        return;
    }
    if (strcmp(resource, "sibur") == 0) {
        player->set_object = SIBUR;
        return;
    }
    set_set_resources_2(game, player, resource);
}

void set_freeze(game_t *game, player_t *player, char *buffer)
{
    char **cmd = my_str_to_word_array(buffer, " ");
    char *resource = NULL;

    if (cmd[1] == NULL) {
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    resource = cmd[1];
    set_set_resources(game, player, resource);
    if (player->set_object == -1) {
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    player->freeze_clock = 7;
    player->last_action = SET;
}

void action_set(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map, player->pos_x, player->pos_y);
    char *msg = malloc(sizeof(char) * 100);

    msg[0] = '\0';
    if (tile == NULL) {
        send(player->socket, "ko\n", 3, 0);
        free(msg);
        return;
    }
    action_set_2(game, player, tile, &msg);
    if (msg != NULL || msg[0] != '\0') {
        send_to_all_graphic(game, msg);
        send_to_all_graphic(game, format_bct(tile, player->pos_x,player->pos_y));
        send_to_all_graphic(game, format_pin(player));
    }
    player->last_action = -1;
    player->set_object = -1;
    player->freeze_clock = 0;
    player->is_freeze = false;
}
