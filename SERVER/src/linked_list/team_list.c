/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** team_list
*/

#include "server.h"

/// @brief ajoute la team à la fin de la liste chainée
/// @param head
/// @param player
void create_team_back(team_t **head, team_t *player)
{
    team_t *tmp = NULL;

    if (*head == NULL) {
        *head = player;
        (*head)->next = NULL;
    } else {
        tmp = *head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = player;
        tmp->next->next = NULL;
    }
}

/// @brief retourne une team en fonction de son nom, NULL si elle n'existe pas
/// @param head
/// @param name
/// @return team_t* || NULL
team_t *get_team_at_name(team_t *head, char *name)
{
    team_t *result = NULL;
    team_t *current = head;
    team_t *next = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            result = current;
            return result;
        }
        next = current->next;
        current = next;
    }
    return NULL;
}

int get_team_number(team_t *head)
{
    int n = 0;

    while (head) {
        n++;
        head = head->next;
    }
    return n;
}

int get_player_number(player_t *head)
{
    int n = 0;

    while (head) {
        n++;
        head = head->next;
    }
    return n;
}

int get_total_player_number(game_t *game)
{
    int n = 0;
    team_t *tmp = game->teams;

    while (tmp) {
        if (strcmp(tmp->name, "GRAPHIC") != 0)
            n += get_player_number(tmp->players);
        tmp = tmp->next;
    }
    return n;
}
