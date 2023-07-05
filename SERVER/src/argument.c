/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** argument
*/

#include "server.h"

void set_team_slots(server_t *server)
{
    team_t *team = server->game->teams;

    if (team == NULL)
        return;
    while (team) {
        team->slots = server->game->clientsNb;
        team = team->next;
    }
}

/// @brief initialise une team et la retourne
/// @param name
/// @return
team_t *create_team(server_t *server, char *name)
{
    team_t *team = malloc(sizeof(team_t));

    team->name = strdup(name);
    team->slots = server->game->clientsNb;
    team->players = NULL;
    team->eggs = NULL;
    team->eggs_nb = 0;
    team->next = NULL;
    return team;
}

/// @brief ajoute les teams à la liste chainée
/// @param server
/// @param argv
/// @param argc
void add_teams(server_t *server, char *argv[], int argc)
{
    int i = optind;
    while (i < argc && *argv[i] != '-') {
        create_team_back(&server->game->teams, create_team(server, argv[i]));
        i++;
    }
    optind = i;
}

void parse_arguments_bis(int opt, server_t *server, char *argv[], int argc)
{
    switch(opt) {
        case 'n':
            optind--;
            add_teams(server, argv, argc);
            break;
        case 'c':
            server->game->clientsNb = strtol(optarg, NULL, 10);
            errno == ERANGE ? exit(84) : 0;
            server->game->clientsNb < 1 ? exit(84) : 0;
            break;
        case 'f':
            server->game->freq = atoi(optarg) * 1.0;
            server->game->freq < 2 ? exit(84) : 0;
            break;
        case '?':
            printf("unknown option: %c\n", opt);
            break;
        default:
            exit(84);
            break;
    }
}

/// @brief parse les arguments du serveur
/// @param argc
/// @param argv
/// @param server
void parse_arguments(int argc, char *argv[], server_t *server)
{
    int opt;

    while((opt = getopt(argc, argv, "p:x:y:n:c:f:")) != -1) {
        switch(opt) {
            case 'p':
                server->port = atoi(optarg);
                break;
            case 'x':
                server->game->width = atoi(optarg);
                break;
            case 'y':
                server->game->height = atoi(optarg);
                break;
            default:
                parse_arguments_bis(opt, server, argv, argc);
                break;
        }
    }
    set_team_slots(server);
}
