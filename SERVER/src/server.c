/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** server
*/

#include "server.h"

int create_socket(server_t *server)
{
    int opt = 1;
    server->master_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server->master_socket == 0) {
        exit(84);
    }
    if (setsockopt(server->master_socket, SOL_SOCKET, SO_REUSEADDR | 15,
    &opt, sizeof(opt)) < 0) {
        exit(84);
    }
    server->max_fd = server->master_socket;
    return 0;
}

int bind_socket(server_t *server)
{
    memset(&server->address, 0, sizeof(server->address));
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->addrlen = sizeof(server->address);
    if (bind(server->master_socket, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0) {
        exit(84);
    }
    return 0;
}

int listen_socket(server_t *server)
{
    if (listen(server->master_socket, SOMAXCONN) < 0) {
        exit(84);
    }
    return 0;
}

int accept_connection(server_t *server)
{
    if ((server->new_socket = accept(server->master_socket,
    (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0) {
        exit(84);
    }
    return 0;
}
