/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** content
*/

#ifndef CONTENT_H_
    #define CONTENT_H_

    /// @brief structure pour les teams
    typedef struct team_s {
        char *name;
        int slots;
        int eggs_nb;
        struct player_s *players;
        struct team_s *next;
        struct egg_s *eggs;
    } team_t;

    /// @brief structure pour les joueurs
    typedef struct player_s {
        int id;
        char *buffer;
        int pos_x;
        int pos_y;
        int socket;
        int orientation;
        bool connected;
        int *ressources;
        int level;
        char *look;

        bool is_freeze;
        int freeze_clock;
        int food_clock;
        int last_action;

        int take_object;
        int set_object;
        char *broadcast_text;

        struct player_s *next;
        struct team_s *team;
        struct player_s **players_on_tile;
    } player_t;

    typedef struct egg_s {
        int pos_x;
        int pos_y;
        int time;
        int id;
        bool is_hatched;
        struct team_s *team;
        struct egg_s *next;
    } egg_t;

    /// @brief structure pour le jeu
    typedef struct game_s {
        bool running;
        size_t width;
        size_t height;
        size_t clientsNb;
        double freq;
        unsigned int id_count;

            int cpt;
        int resources_clock;

        struct team_s *teams;
        struct tile_s **map;
    } game_t;

    typedef struct tile_s {
        int *ressources;
        struct egg_s *eggs;
        struct player_s *players;
    } tile_t;

    //game functions

    void generate_resources(game_t *game);
    void clock_resources(game_t *game);

#endif /* !CONTENT_H_ */
