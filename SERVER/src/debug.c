/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** debug
*/

#include "server.h"

void print_map(game_t *game)
{
    for (size_t x = 0; x < game->width; x++)
        for (size_t y = 0; y < game->height; y++) {
            printf("Tile %ld %ld:\n", x, y);
            for (int i = 0; i < 7; i++) {
                printf("\tresources %d: %d\n", i, game->map[x][y].ressources[i]);
            }
        }
}

void print_players(player_t *player)
{
    if (player == NULL)
        printf("there is no player to display\n");
    while (player != NULL) {
        printf("\t");
        printf("Player id : %d\n", player->id);
        printf("\t");
        printf("Player socket : %d\n", player->socket);
        printf("\t");
        printf("Player pos_x : %d\n", player->pos_x);
        printf("\t");
        printf("Player pos_y : %d\n", player->pos_y);
        printf("\t");
        printf("Player orientation : %d\n", player->orientation);
        printf("\t");
        printf("Player last action : %d\n", player->last_action);
        printf("\t");
        printf("Player freeze time : %d\n", player->freeze_clock);
        player = player->next;
    }
}

void print_teams(team_t *team)
{
    if (team == NULL)
        printf("there is no team to display");
    while (team != NULL) {
        printf("Team name : %s\n", team->name);
        printf("Team slots : %d\n", team->slots);
        print_players(team->players);
        printf("\n\n");
        team = team->next;
    }
}
