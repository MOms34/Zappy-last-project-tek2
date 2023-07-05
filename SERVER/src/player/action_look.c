/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "server.h"


void check_vision_valid(game_t *game, int *x, int *y)
{
    if (*y < 0)
        *y = game->height + *y;
    if (*y >= game->height)
        *y = *y - game->height;
    if (*x < 0)
        *x = game->width + *x;
    if (*x >= game->width)
        *x = *x - game->width;
}

char *get_r_for_tile_4(player_t *player, int lvl, int i, game_t *game)
{
    char *ressource = malloc(sizeof(char) * 3000);
    char *ressource2 = malloc(sizeof(char) * 3000);

    memset(ressource2, 0, 3000);
    memset(ressource, 0, 3000);


    int x = player->pos_x + lvl - i;
    int y = player->pos_y + lvl;
    check_vision_valid(game, &x, &y);
    if (player->orientation == SOUTH) {
            ressource = strcat(ressource, get_name_player_on_tile(get_tile_by_pos(game->map, x, y)));
            ressource2 = strcat(ressource2, get_name_ressources_on_tile(get_tile_by_pos(game->map, x, y)));
    } else
        return "\0";
    if (ressource2 == NULL || ressource == NULL) {
        if (ressource != NULL)
            return ressource;
        else
            return ressource2;
    } else {
        strcat(ressource, " ");
        strcat(ressource, ressource2);
        return ressource;
    }
}

char *get_r_for_tile_3(player_t *player, int lvl, int i, game_t *game)
{
    char *ressource = malloc(sizeof(char) * 3000);
    char *ressource2 = malloc(sizeof(char) * 3000);

    memset(ressource2, 0, 3000);
    memset(ressource, 0, 3000);
    int x = player->pos_x - lvl;
    int y = player->pos_y + lvl - i;
    check_vision_valid(game, &x, &y);
    if (player->orientation == WEST) {
            ressource = strcat(ressource, get_name_player_on_tile(get_tile_by_pos(game->map, x, y)));
            ressource2 = strcat(ressource2, get_name_ressources_on_tile(get_tile_by_pos(game->map, x, y)));
    } else
        return get_r_for_tile_4(player, lvl, i, game);
    if (ressource2 == NULL || ressource == NULL) {
        if (ressource != NULL)
            return ressource;
        else
            return ressource2;
    } else {
        strcat(ressource, " ");
        strcat(ressource, ressource2);
        return ressource;
    }
}
char *get_r_for_tile_2(player_t *player, int lvl, int i, game_t *game)
{
    char *ressource = malloc(sizeof(char) * 3000);
    char *ressource2 = malloc(sizeof(char) * 3000);

    memset(ressource2, 0, 3000);
    memset(ressource, 0, 3000);

    int x = player->pos_x + lvl;
    int y = player->pos_y - lvl + i;
    check_vision_valid(game, &x, &y);
    if (player->orientation == EAST) {
        ressource = strcat(ressource, get_name_player_on_tile(get_tile_by_pos(game->map, x, y)));
        ressource2 = strcat(ressource2, get_name_ressources_on_tile(get_tile_by_pos(game->map, x, y)));
    } else
        return get_r_for_tile_3(player, lvl, i, game);
    if (ressource2 == NULL || ressource == NULL) {
        if (ressource != NULL)
            return ressource;
        else
            return ressource2;
    } else {
        strcat(ressource, " ");
        strcat(ressource, ressource2);
        return ressource;
    }
}

char *get_r_for_tile(player_t *player, int lvl, int i, game_t *game)
{
    char *ressource = malloc(sizeof(char) * 3000);
    char *ressource2 = malloc(sizeof(char) * 3000);

    memset(ressource2, 0, 3000);
    memset(ressource, 0, 3000);
    int x = player->pos_x - lvl + i;
    int y = player->pos_y - lvl;
    check_vision_valid(game, &x, &y);
    if (player->orientation == NORTH ) {
        ressource = strcat(ressource, get_name_player_on_tile(get_tile_by_pos(game->map, x, y)));
        ressource2 = strcat(ressource2, get_name_ressources_on_tile(get_tile_by_pos(game->map, x, y)));
    } else
        return get_r_for_tile_2(player, lvl, i, game);
    if (ressource2 == NULL || ressource == NULL) {
        if (ressource != NULL)
            return ressource;
        else
            return ressource2;
    } else {
        strcat(ressource, " ");
        strcat(ressource, ressource2);
        return ressource;
    }
}

char *get_ressource_orientation_lvl(game_t *game, player_t *player, int lvl)
{
    char *ressource = malloc(sizeof(char) * 3000);
    int max = 1 + (2 * lvl);
    int temp = 0;

    memset(ressource, 0, 3000);
    for (int i = 0; i < max; i++) {
        char *r = get_r_for_tile(player, lvl, i, game);
        if (r != NULL) {
            if (temp > 0) {
                ressource = strcat(ressource, ",");
            }
            ressource = strcat(ressource, r);
            temp++;
        }
    }
    return ressource;
}

void look_cmd(game_t *game, player_t *player)
{
    tile_t *tile = get_tile_by_pos(game->map,
    player->pos_x, player->pos_y);

    player->look = malloc(sizeof(char) * 3000);
    player->look = memset(player->look, 0, 3000);
    player->freeze_clock = 0;
    player->is_freeze = false;
    player->last_action = -1;
    sprintf(player->look, "[ player");
    if (get_name_ressources_on_tile(tile) != NULL && get_name_ressources_on_tile(tile)[0] != '\0') {
        player->look = strcat(player->look, " ");
        player->look = strcat(player->look, get_name_ressources_on_tile(tile));
    }
    for (int i = 1; i <= player->level; i++) {
        if (i == 1) {
            player->look = strcat(player->look, ",");
            player->look = strcat(player->look, get_ressource_orientation_lvl(game, player, i));
        } else {
            player->look = strcat(player->look, ",");
            player->look = strcat(player->look, get_ressource_orientation_lvl(game, player, i));
        }
    }
    strcat(player->look, " ]\n");
    send(player->socket, player->look, strlen(player->look), 0);

}