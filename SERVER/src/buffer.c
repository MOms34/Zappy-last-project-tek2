/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL: Ubuntu]
** File description:
** buffer
*/

#include "server.h"

/// @brief Supprime le délimiteur de fin de commande
/// @param command
/// @return
char *delete_eof(char *command)
{
    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    return command;
}

/// @brief Vérifie si le buffer du joueur contient le délimiteur de fin de
/// commande et exécute les commandes si c'est le cas (en les séparant si
/// plusieurs commandes sont dans le buffer)
/// @param server
/// @param player
/// @param tab
/// @param index
void cut_and_exec(server_t *server, player_t *player, char **tab,
    __attribute__((unused)) int index)
{
    int i = 0;

    if (array_len(tab) == 1) {
        parse_request(server, delete_eof(tab[0]), player);
        if (player != NULL)
            player->buffer = '\0';
        return;
    } else if (array_len(tab) == 0)
        return;
    for (i = 0; tab[i + 1] != NULL; i++)
        parse_request(server, delete_eof(tab[i]), player);
    if (tab[i][strlen(tab[i]) - 1] == '\n') {
        parse_request(server, delete_eof(tab[i]), player);
        if (player != NULL)
            player->buffer = '\0';
    } else
        player->buffer = tab[i];
}

/// @brief Vérifie si le buffer du joueur contient le délimiteur de fin de
/// commande
/// @param server
/// @param player
/// @param i
void eof_reach(server_t *server, player_t *player, int i)
{
    char **tab = NULL;

    for (int i = 0; player->buffer[i] != '\0'; i++) {
        if (player->buffer[i] == '\n') {
            tab = my_str_to_word_array(player->buffer, "\n");
            break;
        }
    }
    if (tab != NULL)
        cut_and_exec(server, player, tab, i);
}
