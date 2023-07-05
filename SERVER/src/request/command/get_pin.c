/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** get_pin
*/

#include "server.h"

void get_pin(server_t *server, player_t *player, char *buffer)
{
    char **tab = my_str_to_word_array(buffer, " ");
    player_t *tmp = NULL;

    if (tab[1] == NULL) {
        send(player->socket, "sbp\n", 4, 0);
        return;
    }
    tmp = get_player_at_socket(server, atoi(tab[1]));
    if (tmp == NULL) {
        send(player->socket, "sbp\n", 4, 0);
        return;
    }
    send_to_all_graphic(server->game, format_pin(tmp));
}

void get_ppo(server_t *server, player_t *player, char *buffer)
{
    char *msg = malloc(sizeof(char) * (100));
    char **tab = my_str_to_word_array(buffer, " ");
    player_t *tmp = NULL;

    if (tab[1] == NULL) {
        send(player->socket, "sbp\n", 4, 0);
        return;
    }
    tmp = get_player_at_socket(server, atoi(tab[1]));
    if (tmp == NULL) {
        send(player->socket, "sbp\n", 4, 0);
        return;
    }
    sprintf(msg, "ppo %d %d %d %d\n", tmp->socket, tmp->pos_x,
        tmp->pos_y, tmp->orientation);
    send_to_all_graphic(server->game, msg);
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}
