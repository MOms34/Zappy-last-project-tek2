/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_inventory
*/

#include "server.h"

char *format_pin(player_t *player)
{
    char *pin = malloc(sizeof(char) * 1000);

    sprintf(pin, "pin %d %d %d %d %d %d %d %d %d %d\n", player->socket,
        player->pos_x, player->pos_y, player->ressources[FOOD],
        player->ressources[LINEMATE], player->ressources[DERAUMERE],
        player->ressources[SIBUR], player->ressources[MENDIANE],
        player->ressources[PHIRAS], player->ressources[THYSTAME]);
    return pin;
}

void action_inventory(game_t *game, player_t *player)
{
    char *response = "[";

    response = my_strcat(my_strcat(my_strcat(response, "food "),
    my_itoa(player->ressources[FOOD])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "linemate "),
    my_itoa(player->ressources[LINEMATE])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "deraumere "),
    my_itoa(player->ressources[DERAUMERE])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "sibur "),
    my_itoa(player->ressources[SIBUR])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "mendiane "),
    my_itoa(player->ressources[MENDIANE])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "phiras "),
    my_itoa(player->ressources[PHIRAS])), ", ");
    response = my_strcat(my_strcat(my_strcat(response, "thystame "),
    my_itoa(player->ressources[THYSTAME])), "]\n");
    send(player->socket, response, strlen(response), 0);
    player->freeze_clock = 0;
    player->last_action = -1;
    player->is_freeze = false;
}
