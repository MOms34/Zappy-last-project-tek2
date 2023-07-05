/*
** EPITECH PROJECT, 2023
** epitech momo
** File description:
** momo
*/

#include "server.h"

int *ressoources_per_lvl(int lvl)
{
    int **ressources = malloc(sizeof(int*) * 8);
    int temp_1[7] = {1, 1, 0, 0, 0, 0, 0};
    int temp_2[7] = {2, 1, 1, 1, 0, 0, 0};
    int temp_3[7] = {2, 2, 0, 1, 0, 2, 0};
    int temp_4[7] = {4, 1, 1, 2, 0, 1, 0};
    int temp_5[7] = {4, 1, 2, 1, 3, 0, 0};
    int temp_6[7] = {6, 1, 2, 3, 0, 1, 0};
    int temp_7[7] = {6, 2, 2, 2, 2, 2, 1};

    for (int i = 0; i < 8; i++) {
        ressources[i] = malloc(sizeof(int) * 7);
        if (i == 1) {
            memcpy(ressources[i], temp_1, sizeof(int) * 7);
        } else if (i == 2) {
            memcpy(ressources[i], temp_2, sizeof(int) * 7);
        } else if (i == 3) {
            memcpy(ressources[i], temp_3, sizeof(int) * 7);
        } else if (i == 4) {
            memcpy(ressources[i], temp_4, sizeof(int) * 7);
        } else if (i == 5) {
            memcpy(ressources[i], temp_5, sizeof(int) * 7);
        } else if (i == 6) {
            memcpy(ressources[i], temp_6, sizeof(int) * 7);
        } else if (i == 7) {
            memcpy(ressources[i], temp_7, sizeof(int) * 7);
        }
    }

    return ressources[lvl];
}


bool check_ressource_in_tile(tile_t *tile, int *ressource)
{
    int i = 1;

    if (!tile || !tile->ressources || !ressource)
        return false;
    if (get_nb_players_on_tile(tile) < ressource[0])
        return false;
    while (i < 7) {
        if (tile->ressources[i] < ressource[i])
            return false;
        i++;
    }
    return true;
}

int players_same_lvl(tile_t *tile, player_t *player, int lvl)
{
    int nb = 1;
    player_t *tmp = NULL;

    tmp = tile->players;
    if (!tmp) {
        return 0;
    }
    while (tmp) {
        if (tmp->level == lvl && tmp->is_freeze == false && tmp->socket != player->socket)
            nb++;
        tmp = tmp->next;
    }
    return nb;
}

void lvl_up(player_t **player, int level_ref)
{
    int i = 0;

    while (player[i]) {
        player[i]->level = level_ref + 1;
        i++;
    }
    return;
}

void freeze_players(player_t **players, bool freeze)
{
    int i = 0;

    while (players[i]) {
        if (freeze == true) {
            players[i]->is_freeze = true;
            players[i]->freeze_clock = 300;
            players[i]->last_action = INCANTATION;
        } else {
            players[i]->is_freeze = false;
            players[i]->freeze_clock = 0;
            players[i]->last_action = -1;
        }
        i++;
    }
    return;
}

void delete_items(tile_t *tile, int *ressource)
{
    int i = 1;

    while (i < 7) {
        tile->ressources[i] -= ressource[i];
        i++;
    }
    return;
}

void incantation_succes(player_t *player, tile_t *tile, int *lvl_r, game_t *game)
{
    char *response = malloc(sizeof(char) * 1000);
    char *gui_response = malloc(sizeof(char) * 256);
    int *lvl_ressources = ressoources_per_lvl(player->level);
    struct player_s **current_player = NULL;
    int nb_same_lvl = players_same_lvl(tile, player, player->level);
    char *pic = malloc(sizeof(char) * 1000);
    char *plv = malloc(sizeof(char) * 1000);
    plv = memset(plv, 0, 1000);
    pic = memset(pic, 0, 1000);

    if (!check_ressource_in_tile(tile, lvl_ressources) || nb_same_lvl < lvl_ressources[0] || player->is_freeze == false)
        return invalid_incantation_succes(player, game, nb_same_lvl);
    if (player->players_on_tile == NULL) {
        player->freeze_clock = 0;
        player->is_freeze = false;
        player->last_action = -1;
        return;
    }
    freeze_players(player->players_on_tile, false);
    lvl_up(player->players_on_tile, lvl_ressources[0]);
    delete_items(tile, lvl_r);
    sprintf(gui_response, "pie %d %d 1\n", player->pos_x, player->pos_y);
    send_to_all_graphic(game, gui_response);
    sprintf(response, "Current level: %d\n", player->level);
    current_player = player->players_on_tile;
    while (*current_player != NULL) {
        send((*current_player)->socket, response, strlen(response), 0);
        sprintf(plv, "plv %d %d\n", (*current_player)->socket, (*current_player)->level);
        send_to_all_graphic(game, plv);
        current_player++;
    }
    free(response);
    return;
}

void incantation(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map,
    player->pos_x, player->pos_y);
    int nb_players = get_nb_players_on_tile(tile);
    int *lvl_ressources = ressoources_per_lvl(player->level);
    int nb_same_lvl = players_same_lvl(tile, player, player->level);
    player_t **players = get_players_to_incant(tile, player, nb_players);
    char *gui_response = malloc(sizeof(char) * 1000);
    memset(gui_response, 0, 1000);
    struct player_s **current_player = NULL;

    printf("nb_players = %d\n", nb_players);
    printf("nb_same_lvl = %d\n", nb_same_lvl);
    printf("lvllvl_ressources[0] = %d\n",lvl_ressources[0]);
    printf("player->level = %d\n", player->level);

    if (!check_ressource_in_tile(tile, lvl_ressources) || nb_same_lvl <lvl_ressources[0]) {
        if (get_all_graphic(game, player) != NULL)
            sprintf(gui_response, "pic %d %d %d%s\n", player->pos_x, player->pos_y, player->level, get_all_graphic(game, player));
        else 
            sprintf(gui_response, "pic %d %d %d %d\n", player->pos_x, player->pos_y, player->level);
        send_to_all_graphic(game, gui_response);
        send(player->socket, strdup("ko\n"), 3, 0);
        player->players_on_tile = NULL;
        player->last_action = INCANTATION;

        return;
    } else {
        player->players_on_tile = players;
        freeze_players(players, true);
        current_player = player->players_on_tile;
        if (get_all_graphic(game, player) != NULL)
            sprintf(gui_response, "pic %d %d %d%s\n", player->pos_x, player->pos_y, player->level, get_all_graphic(game, player));
        else 
            sprintf(gui_response, "pic %d %d %d %d\n", player->pos_x, player->pos_y, player->level);
        while (*current_player != NULL) {
            send((*current_player)->socket, "Elevation underway\n", 19, 0);
            current_player++;
        }
        send_to_all_graphic(game, gui_response);
    }
    if (!check_ressource_in_tile(tile, lvl_ressources) || nb_same_lvl <lvl_ressources[0]) {
        send(player->socket, strdup("ko\n"), 3, 0);
        return;
    }
}

void incantation_cmd(game_t *game, player_t *player)
{
    if (player->level == 8) {
        send(player->socket, strdup("ko\n"), 3, 0);
        return;
    }
    incantation(game, player);
    return;
}
