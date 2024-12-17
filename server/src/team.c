/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** server.c
*/
#include "server.h"
#include "teams.h"
#include <stdint.h>

egg_t add_new_egg_to_team(team_t *team, pos_t egg_pos)
{
    static uint64_t id = 0;
    egg_t new_egg = {id, egg_pos};

    team->eggs = realloc(team->eggs, sizeof(egg_t) * (team->nb_eggs + 1));
    team->eggs[team->nb_eggs] = new_egg;
    team->nb_eggs++;
    team->max_clients += 1;
    id++;
    return new_egg;
}

team_t *get_team_by_name(void *server_ptr, char *name)
{
    server_t *server = (server_t *)server_ptr;

    for (int i = 0; server->teams[i] != NULL; i++) {
        if (strcmp(server->teams[i]->name, name) == 0)
            return server->teams[i];
    }
    return NULL;
}
