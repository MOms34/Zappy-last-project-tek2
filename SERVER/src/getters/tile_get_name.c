/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "server.h"

char* get_index_name_ressources(int resource_index)
{
    switch (resource_index ) {
        case FOOD:
            return "food";
        case LINEMATE:
            return "linemate";
        case DERAUMERE:
            return "deraumere";
        case SIBUR:
            return "sibur";
        case MENDIANE:
            return "mendiane";
        case PHIRAS:
            return "phiras";
        case THYSTAME:
            return "thystame";
        default:
            return NULL;
    }
}

char* get_resource_name(int resource_index, int number)
{
    char *names = get_index_name_ressources(resource_index);
    char* name = malloc(3000);

    if (resource_index < 0 || resource_index > 7 || number == 0 || number < 0)
        return NULL;
    memset(name, 0, 3000);
    for(int i = 0; i < number; i++) {
        if (i == 0) {
            strcpy(name, names);
        }
        else {
            strcat(name, " ");
            strcat(name, names);
            }
    }
    return name;
}

char* get_name_ressources_on_tile(tile_t* tile)
{
    char* names = malloc(3000);
    char* res_name = NULL;
    int z = 0;

    names[0] = '\0';
    if (!tile || !tile->ressources)
        return NULL;
    for (int i = 0; i < 7; i++) {
        res_name = NULL;
        res_name = get_resource_name(i, tile->ressources[i]);

        if (res_name != NULL) {
            strcat(names, z > 0 ? " " : "");
            strcat(names, res_name);
            z++;
        } else {
            free(res_name);
        }
    }
    return names;
}

char *get_name_player_on_tile(tile_t *tile)
{
    player_t *tmp = tile->players;
    char *names = NULL;
    char *tmp_name = NULL;
    char *temp = NULL;

    while (tmp) {
        tmp_name = malloc(strlen("player") + 1);
        sprintf(tmp_name, "player");

        if (!names) {
            names = strdup(tmp_name);
        } else {
            temp = malloc(strlen(names) + strlen(tmp_name) + 2);
            sprintf(temp, "%s %s", names, tmp_name);
            free(names);
            names = temp;
        }
        free(tmp_name);
        tmp = tmp->next;
    }
    return (names != NULL) ? names : "\0";
}
