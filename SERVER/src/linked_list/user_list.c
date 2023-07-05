/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL: Ubuntu]
** File description:
** content
*/

#include "server.h"

/// @brief ajoute le joueur à la fin de la liste chainée
/// @param head
/// @param player
void create_player_back(player_t **head, player_t *player)
{
    player_t *tmp = NULL;

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

void delete_player_at_socket(player_t **head, int socket)
{
    player_t *tmp = *head;
    player_t *tmp2 = NULL;

    while (tmp) {
        if (tmp->socket == socket) {
            *head = tmp->next;
            free(tmp);
            return;
        }
        if (tmp->next->socket == socket) {
            tmp2 = tmp->next;
            tmp->next = tmp2->next;
            free(tmp2);
            break;
        }
        tmp = tmp->next;
    }
}

player_t *get_player_at_socket_bis(player_t *head, int socket)
{
    player_t *tmp = head;

    while (tmp) {
        if (tmp->socket == socket) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

player_t *get_player_at_socket_bis_bis(server_t *server, int socket,
    player_t *tmp2)
{
    tmp2 = server->queue;
    while (tmp2) {
        if (tmp2->socket == socket)
            return tmp2;
        tmp2 = tmp2->next;
    }
    return NULL;
}

/// @brief prend en paramètre la liste des teams présente dans server->teams
/// @brief er cherche dans chaque team si un joueur est présent avec le
/// @brief socket passé en paramètre
/// @param head liste des teams server-teams
/// @param socket socket du joueur à chercher
/// @return retourne le joueur si il est trouvé, sinon NULL
player_t *get_player_at_socket(server_t *server, int socket)
{
    team_t *tmp = server->game->teams;
    player_t *tmp2 = NULL;

    while (tmp) {
        if (tmp->players != NULL)
            tmp2 = get_player_at_socket_bis(tmp->players, socket);
        if (tmp2 != NULL) {
            return tmp2;
        }
        tmp = tmp->next;
    }
    return get_player_at_socket_bis_bis(server, socket, tmp2);
}
