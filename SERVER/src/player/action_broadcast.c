/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_broadcast
*/

#include "server.h"

int calculate_r_direction(int dx, int dy, int direction)
{
    int r_direction = 0;
    double angle = atan2(dy, dx) * 180.0 / M_PI;

    angle += direction * 45.0;
    angle = fmod(angle + 360.0, 360.0);
    r_direction = ((int)(angle / 45.0) + 1) % 9;
    if (r_direction == 0) r_direction = 1;
    return r_direction;
}

void send_broadcast(game_t *game, player_t *player, player_t *tmp)
{
    char *ia_msg = malloc(sizeof(char) * 255);
    int dx = tmp->pos_x - player->pos_x;
    int dy = tmp->pos_y - player->pos_y;
    int shortest_dx = min(abs(dx), game->width - abs(dx));
    int shortest_dy = min(abs(dy), game->height - abs(dy));
    int direction = calculate_r_direction(shortest_dx, shortest_dy,
    tmp->orientation);
    sprintf(ia_msg, "message %d, %s\n", direction, player->broadcast_text);
    send(tmp->socket, ia_msg, strlen(ia_msg), 0);
    free(ia_msg);
}

void process_players(game_t *game, player_t *player, player_t *list)
{
    player_t *tmp = list;

    while (tmp) {
        if (tmp->socket != player->socket && strcmp(tmp->team->name,
        "GRAPHIC") != 0)
            send_broadcast(game, player, tmp);
        tmp = tmp->next;
    }
}

void action_broadcast(game_t *game, player_t *player)
{
    team_t *team = game->teams;
    char *gui_msg = malloc(sizeof(char) * 255);

    while (team) {
        if (team->players != NULL)
            process_players(game, player, team->players);
        team = team->next;
    }
    player->is_freeze = false;
    player->last_action = -1;
    player->freeze_clock = 0;
    send(player->socket, "ok\n", 3, 0);
    sprintf(gui_msg, "pbc %d %s\n", player->socket, player->broadcast_text);
    player->broadcast_text = NULL;
    send_to_all_graphic(game, gui_msg);
}

void broadcast_freeze(game_t *game, player_t *player, char *buffer)
{
    char **tmp = my_str_to_word_array(buffer, " ");

    if (tmp[1] == NULL) {
        player->is_freeze = false;
        player->last_action = -1;
        player->freeze_clock = 0;
        player->broadcast_text = NULL;
        send(player->socket, "ko\n", 3, 0);
        return;
    }
    player->last_action = BROADCAST;
    player->freeze_clock = 7;
    player->broadcast_text = strdup(tmp[1]);
}
