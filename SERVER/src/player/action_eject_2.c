/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** action_eject_2
*/

#include "server.h"

void eject_west(game_t *game, player_t *player, tile_t *tile)
{
    player_t *list = tile->players;

    while (list) {
        if (list->socket != player->socket) {
            delete_player_from_tile(tile, list);
            move_west(game, list);
            send(list->socket, "eject:4\n", 8, 0);
        }
        list = list->next;
    }
}

void eject_eggs(game_t *game, tile_t *tile)
{
    egg_t *list = tile->eggs;
    char *gui_msg = NULL;

    while (list) {
        if (list->is_hatched == true) {
            gui_msg = malloc(sizeof(char) * 200);
            sprintf(gui_msg, "edi %d\n", list->id);
            send_to_all_graphic(game, gui_msg);
            list->team->slots -=1;
            delete_egg_at_id(&list->team->eggs, list->id);
        }
        list = list->next;
    }
    tile->eggs = NULL;
}
