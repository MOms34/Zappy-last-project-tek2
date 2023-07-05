/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "server.h"

void invalid_incantation_succes(player_t *player, game_t* game, int nb_pl)
{
    struct player_s **current_player = player->players_on_tile;
    char *str = malloc(sizeof(char) * 100);

    sprintf(str, "pie %d %d 0\n", player->pos_x, player->pos_y);
    send_to_all_graphic(game, str);
    while (player->players_on_tile != NULL && nb_pl > 1) {
        send((*current_player)->socket, strdup("ko\n"), 3, 0);
        current_player++;
    }
    if (player->players_on_tile != NULL)
        freeze_players(player->players_on_tile, false);
    player->is_freeze = false;
    player->last_action = -1;
    player->freeze_clock = 0;
    return;

}
