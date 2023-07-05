/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** clock
*/

#include "server.h"

int get_freeze_time_cmd(player_t *player)
{
    if (player->last_action == -1)
        return 0;
    if (player->last_action == FORWARD || player->last_action == RIGHT ||
    player->last_action == LEFT || player->last_action == LOOK ||
    player->last_action == BROADCAST || player->last_action == EJECT ||
    player->last_action == TAKE || player->last_action == SET)
        return (7);
    if (player->last_action == INCANTATION)
        return (300);
    if (player->last_action == FORK)
        return (42);
    if (player->last_action == INVENTORY)
        return (1);
    return (0);
}

void process_action(player_t *player, game_t *game)
{
    if (player->last_action == INCANTATION)
        incantation_succes(player, get_tile_by_pos(game->map, player->pos_x,
        player->pos_y), ressoources_per_lvl(player->level), game);
    if (player->last_action == FORK)
        action_fork(game, player);
    if (player->last_action == INVENTORY)
        action_inventory(game, player);
    if (player->last_action == FORWARD)
        action_forward(game, player);
    if (player->last_action == RIGHT || player->last_action == LEFT)
        action_turn(game, player);
    if (player->last_action == LOOK)
        look_cmd(game, player);
    if (player->last_action == BROADCAST)
        action_broadcast(game, player);
    if (player->last_action == EJECT)
        action_eject(game, player);
    if (player->last_action == TAKE)
        action_take(game, player);
    if (player->last_action == SET)
        action_set(game, player);
}

void remove_player(player_t *player, game_t *game)
{
    char *msg = malloc(sizeof(char) * 100);

    send(player->socket, "dead\n", 5, 0);
    sprintf(msg, "pdi %d\n", player->socket);
    send_to_all_graphic(game, msg);
    delete_player_from_tile(get_tile_by_pos(game->map, player->pos_x,
    player->pos_y), player);
    delete_player_at_socket(&player->team->players, player->socket);
}

void check_for_freeze_players(player_t *players, game_t *game)
{
    player_t *next_player = NULL;

    while (players != NULL) {
        next_player = players->next;
        if (players->is_freeze && players->freeze_clock > 0)
            players->freeze_clock -= 1;
        if (players->is_freeze && players->freeze_clock <= 0 &&
        players->last_action != -1)
            process_action(players, game);
        if (players->team != NULL && players->food_clock > 0 &&
        strcmp(players->team->name, "GRAPHIC") != 0)
            players->food_clock--;
        if (players->food_clock == 0 && players->ressources[FOOD] > 0 &&
        players->team != NULL && strcmp(players->team->name, "GRAPHIC") != 0) {
            players->ressources[FOOD]--;
            players->food_clock = 126;
        }
        if (players->ressources[FOOD] == 0 && players->food_clock == 0 &&
        players->team != NULL && strcmp(players->team->name, "GRAPHIC") != 0)
            remove_player(players, game);
        players = next_player;
    }
}

void check_for_eggs(game_t *game, egg_t *eggs)
{
    char *msg = NULL;

    while (eggs != NULL) {
        if (eggs->is_hatched == false && eggs->time < 600)
            eggs->time += 1;
        if (eggs->time >= 600 && eggs->is_hatched == false) {
            msg = malloc(sizeof(char) * 100);
            eggs->is_hatched = true;
            sprintf(msg, "eht %d\n", eggs->id);
            create_egg_back(&eggs->team->eggs, eggs);
            eggs->team->eggs_nb += 1;
            eggs->team->slots += 1;
            send_to_all_graphic(game, msg);
        }
        eggs = eggs->next;
    }
}

void check_for_freeze(game_t *game)
{
    team_t *tmp = NULL;

    if (game->teams == NULL)
        return;
    tmp = game->teams;
    while (tmp) {
        if (tmp->players)
            check_for_freeze_players(tmp->players, game);
        if (tmp->eggs)
            check_for_eggs(game, tmp->eggs);
        tmp = tmp->next;
    }
}
