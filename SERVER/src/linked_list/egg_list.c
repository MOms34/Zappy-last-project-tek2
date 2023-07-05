/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** egg_list
*/

#include "server.h"

/// @brief ajoute le joueur à la fin de la liste chainée
/// @param head
/// @param egg
void create_egg_back(egg_t **head, egg_t *egg)
{
    egg_t *tmp = NULL;

    if (*head == NULL) {
        *head = egg;
        (*head)->next = NULL;
    } else {
        tmp = *head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = egg;
        tmp->next->next = NULL;
    }
}

void delete_egg_at_id(egg_t **head, int id)
{
    egg_t *tmp = *head;
    egg_t *tmp2 = NULL;

    while (tmp) {
        if (tmp->id == id) {
            *head = tmp->next;
            return;
        }
        if (tmp->next->id == id) {
            tmp2 = tmp->next;
            tmp->next = tmp2->next;
            break;
        }
        tmp = tmp->next;
    }
}
