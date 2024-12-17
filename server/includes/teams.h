/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** teams.h
*/

#pragma once
#include "client.h"
#include "parse_args.h"

struct egg {
    uint64_t id;
    pos_t pos;
};
typedef struct egg egg_t;

struct team {
    char *name;
    client_t **clients;
    int nb_clients;
    int max_clients;
    egg_t *eggs;
    int nb_eggs;
};
typedef struct team team_t;

team_t **init_teams(parse_args_t *args);
team_t *get_team_by_name(void *server_ptr, char *name);
egg_t add_new_egg_to_team(team_t *team, pos_t egg_pos);
