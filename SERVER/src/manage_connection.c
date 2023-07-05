/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** manage_connection
*/

#include "server.h"

static player_t *init_player(int socket, server_t *server)
{
    player_t *player = malloc(sizeof(player_t));

    player->pos_x = 0;
    player->pos_y = 0;
    player->level = 1;
    player->is_freeze = false;
    player->freeze_clock = 0;
    player->last_action = -1;
    player->team = NULL;
    player->id = server->game->id_count + 1;
    server->game->id_count++;
    player->next = NULL;
    player->socket = socket;
    player->connected = false;
    player->orientation = rand() % 4 + 1;
    player->take_object = -1;
    player->set_object = -1;
    player->ressources = malloc(sizeof(int) * 7);
    memset(player->ressources, 0, 7 * sizeof(int));
    player->ressources[FOOD] = 10;
    player->food_clock = 126;
    player->buffer = malloc(sizeof(char) * 1024);
    player->buffer[0] = '\0';
    return (player);
}

int set_select(fd_set *read_fds, int *activity, server_t *server)
{
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 1000000 / server->game->freq;
    *activity = select(server->max_fd + 1, read_fds, NULL, NULL, &timeout);
    return (*activity);
}

void set_new_socket(server_t *server)
{
    if ((server->new_socket = accept(server->master_socket,
    (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0) {
            exit(84);
    }
    for (int i = 0; i < SOMAXCONN; i++) {
        if (server->client_socket[i] == 0) {
            server->client_socket[i] = server->new_socket;
            create_player_back(&server->queue, init_player(server->new_socket
            , server));
            send(server->new_socket, "WELCOME\n", 8, 0);
            break;
        }
    }
}

int add_child_socket(server_t *server, fd_set *read_fds)
{
    int fd = 0;

    FD_ZERO(read_fds);
    FD_SET(server->master_socket, read_fds);
    for (int i = 0; i < SOMAXCONN; i++) {
        fd = server->client_socket[i];
        if (fd > 0)
            FD_SET(fd, read_fds);
        if (fd > server->max_fd)
            server->max_fd = fd;
    }
    return (0);
}

/// @brief Gestion des connexions et écoute de chaque socket connéctée
/// @param server
/// @return
int manage_connection(server_t *server)
{
    fd_set read_fds;
    int activity = 0;

    while (1) {
        add_child_socket(server, &read_fds);
        set_select(&read_fds, &activity, server) == -1 ? exit(84) : 0;
        if (FD_ISSET(server->master_socket, &read_fds))
            set_new_socket(server);
        for (int i = 0; i < SOMAXCONN; i++)
            listen_clients(server, i, &read_fds,
            get_player_at_socket(server,
            server->client_socket[i]));
        game_engine(server);
    }
    return (0);
}
