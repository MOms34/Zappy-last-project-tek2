/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** server
*/

#include "define.h"

#ifndef SERVER_H_
    #define SERVER_H_

    typedef struct thread_args_s {
        struct server_s *server;
        char *buffer;
        struct player_s *player;
    } thread_args_t;

    /// @brief structure du serveur
    /// @param queue liste des joueurs en attente de partie
    typedef struct server_s {
        int port;
        int client_socket[SOMAXCONN];
        struct sockaddr_in address;
        int master_socket;
        int new_socket;
        int max_fd;
        int addrlen;
        int *total_resources;

        struct game_s *game;
        struct player_s *queue;
    } server_t;

    int listen_clients(server_t *server, int i, fd_set *read_fds,
        player_t *player);
    int manage_connection(server_t *server);
    int accept_connection(server_t *server);
    int create_socket(server_t *server);
    int listen_socket(server_t *server);
    int bind_socket(server_t *server);

    void parse_arguments(int argc, char *argv[], server_t *server);
    void eof_reach(server_t *server, player_t *player, int i);

    player_t *get_player_at_socket(server_t *server, int socket);
    void create_player_back(player_t **head, player_t *player);
    void create_team_back(team_t **head, team_t *player);
    void create_egg_back(egg_t **head, egg_t *egg);
    void delete_egg_at_id(egg_t **head, int id);
    team_t *get_team_at_name(team_t *head, char *name);
    int get_team_number(team_t *head);

    void free_memory(server_t *server);
    int get_freeze_time_cmd(player_t *player);

    void handle_not_connected_request(server_t *server, char *buffer,
    player_t *player);
    void handle_gui_request(server_t *server, char *buffer, player_t *player);
    void *parse_request(server_t *server, char *buffer, player_t *player);
    int detect_command(char *buffer);

    void get_tile(server_t *server, char *buffer, player_t *player);
    void get_pin(server_t *server, player_t *player, char *buffer);
    void get_ppo(server_t *server, player_t *player, char *buffer);
    void get_map_size(server_t *server, player_t *player);
    void get_name(server_t *server, player_t *player);
    void get_map(server_t *server, player_t *player);
    int get_total_player_number(game_t *game);

    tile_t *get_tile_by_pos(tile_t **tile, int x, int y);
    tile_t *find_empty_tile(game_t *game);
    int *calculate_resources_available(game_t *game);
    int get_nb_players_on_tile(tile_t *tile);
    void delete_player_at_socket(player_t **head, int socket);
    void delete_player_from_tile(tile_t *tile, player_t *player);
    void eject_eggs(game_t *game, tile_t *tile);
    void eject_west(game_t *game, player_t *player, tile_t *tile);

    void spawn_players(game_t *game, player_t *player);
    void spawn_player(game_t *game, player_t *player);
    void spawn_all_players(game_t *game);

    void print_players(player_t *player);
    void print_teams(team_t *team);
    void print_map(game_t *game);

    char *format_bct(tile_t *tile, int x, int y);
    char *format_pin(player_t *player);

    void start_game(server_t *server);
    void game_engine(server_t *server);
    void send_to_all_players(game_t *game, char *str);
    void send_to_all_graphic(game_t *game, char *str);

    //functions for ancantation
    player_t **get_players_to_incant(tile_t *tile, player_t *player,
    int nb_players);
    int *ressoources_per_lvl(int lvl);
    bool check_ressource_in_tile(tile_t *tile, int *ressource);
    int players_same_lvl(tile_t *tile, player_t *player, int lvl);
    void lvl_up(player_t **player, int level_ref);
    void delete_items(tile_t *tile, int *ressource);
    char *get_all_graphic(game_t *game, player_t *players);
    void invalid_incantation_succes(player_t *player, game_t* game, int
    nb_lvl);
    void incantation_succes(player_t *player, tile_t *tile, int *lvl_r,
    game_t *game);
    void incantation(game_t *game, player_t *player);
    void incantation_cmd(game_t *game, player_t *player);
    void freeze_players(player_t **players, bool freeze);
    void pnw_new_player(game_t *game, player_t *player);

    void move_north(game_t *game, player_t *player);
    void move_south(game_t *game, player_t *player);
    void move_east(game_t *game, player_t *player);
    void move_west(game_t *game, player_t *player);

    void freeze_action(game_t *game, player_t *player, int action,
    char *buffer);
    void take_freeze(game_t *game, player_t *player, char *buffer);
    void set_freeze(game_t *game, player_t *player, char *buffer);
    void check_for_freeze(game_t *game);
    void broadcast_freeze(game_t *game, player_t *player, char *buffer);
    void action_forward(game_t *game, player_t *player);
    void action_turn(game_t *game, player_t *player);
    void action_take(game_t *game, player_t *player);
    void action_set(game_t *game, player_t *player);
    void action_set_2(game_t *game, player_t *player,
    tile_t *tile, char **msg);
    void action_eject(game_t *game, player_t *player);
    void action_inventory(game_t *game, player_t *player);
    void action_fork(game_t *game, player_t *player);
    void action_broadcast(game_t *game, player_t *player);

    char* get_index_name_ressources(int resource_index);
    char* get_resource_name(int resource_index, int number);
    char* get_name_ressources_on_tile(tile_t* tile);
    char *get_name_player_on_tile(tile_t *tile);
    void look_cmd(game_t *game, player_t *player);

    int min(int a, int b);

#endif /* !SERVER_H_ */
