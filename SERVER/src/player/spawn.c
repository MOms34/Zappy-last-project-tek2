/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** spawn
*/

#include "server.h"

void pnw_new_player(game_t *game, player_t *player)
{
    char *str = malloc(sizeof(char) * 200);
    team_t *team = get_team_at_name(game->teams, "GRAPHIC");
    player_t *graphic = NULL;

    if (team == NULL)
        return;
    if (team->players == NULL)
        return;
    graphic = team->players;
    sprintf(str, "pnw %d %d %d %d %d %s\n", player->socket, player->pos_x,
        player->pos_y, player->orientation, player->level, player->team->name);
    while (graphic) {
        send(graphic->socket, str, strlen(str), 0);
        graphic = graphic->next;
    }
    free(str);
}

int spawn_on_egg(egg_t *eggs, char *msg, game_t *game, player_t *player)
{
    while (eggs != NULL) {
        if (eggs->is_hatched == true) {
            player->pos_x = eggs->pos_x;
            player->pos_y = eggs->pos_y;
            player->orientation = rand() % 4 + 1;
            game->map[eggs->pos_x][eggs->pos_y].players = player;
            sprintf(msg, "ebo %d\n", eggs->id);
            send_to_all_graphic(game, msg);
            delete_egg_at_id(&player->team->eggs, eggs->id);
            delete_egg_at_id(&game->map[eggs->pos_x][eggs->pos_y].eggs, eggs->id);
            return 1;
        }
        eggs = eggs->next;
    }
}

void spawn_player(game_t *game, player_t *player)
{
    char *msg = malloc(sizeof(char) * (100));
    egg_t *eggs = player->team->eggs;
    int x = rand() % game->width;
    int y = rand() % game->height;
    int direction = rand() % 4 + 1;

    if (spawn_on_egg(eggs, msg, game, player) == 1)
        return;
    free(msg);
    while (game->map[x][y].players != NULL) {
        x = rand() % game->width;
        y = rand() % game->height;
    }
    player->orientation = direction;
    player->pos_x = x;
    player->pos_y = y;
    game->map[x][y].players = player;
}

void spawn_players(game_t *game, player_t *player)
{
    if (player == NULL)
        return;
    while (player) {
        spawn_player(game, player);
        player = player->next;
    }
}

void spawn_all_players(game_t *game)
{
    team_t *team = NULL;

    team = game->teams;
    if (team == NULL)
        return;
    while (team) {
        spawn_players(game, team->players);
        team = team->next;
    }
}
