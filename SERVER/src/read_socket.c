/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** read_socket
*/

#include "server.h"

/// @brief déconnecte le joueur lorsque la socket est fermée
/// @param server
/// @param i
void logoff(server_t *server, int i)
{
    char *gui_msg = malloc(sizeof(char) * (256));
    player_t *player = get_player_at_socket(server, server->client_socket[i]);

    sprintf(gui_msg, "pdi %d\n", player->socket);
    send_to_all_graphic(server->game, gui_msg);
    if (player != NULL && player->team != NULL) {
        player->team->slots++;
        delete_player_at_socket(&player->team->players, player->socket);
    }
}

void listen_client_bis(server_t *server, player_t *player, int i, char *str)
{
    if (player->buffer == NULL || strlen(player->buffer) == 0)
        player->buffer = strdup(str);
    else
        player->buffer = my_strcat(player->buffer, str);
    eof_reach(server, player, i);
}

/// @brief Récupération du flux de données de la socket et bufferisation
/// @param server
/// @param i index de la socket (pas la socket en elle même)
/// @param read_fds
/// @param player joueur associé à la socket server->client_socket[i]
/// @return
int listen_clients(server_t *server, int i, fd_set *read_fds, player_t *player)
{
    int valread = 0;
    char *str = malloc(sizeof(char) * 1024);
    int fd = server->client_socket[i];

    if (FD_ISSET(fd, read_fds)) {
        if ((valread = read(fd, str, 1024)) == 0) {
            close(fd);
            logoff(server, i);
            server->client_socket[i] = 0;
            return 1;
        } else {
            str[valread] = '\0';
            listen_client_bis(server, player, i, str);
            return 0;
        }
    }
    free(str);
    return 1;
}
