/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** init_teams.c
*/

#include "teams.h"

team_t **init_teams(parse_args_t *args)
{
    team_t **teams =
        malloc(sizeof(team_t *) * ((args->max_clients_per_team) + 1));
    int i = 0;

    for (i = 0; args->teams_name[i] != NULL; i++) {
        teams[i] = malloc(sizeof(team_t));
        teams[i]->name = strdup(args->teams_name[i]);
        teams[i]->max_clients = args->max_clients_per_team;
        teams[i]->nb_clients = 0;
        teams[i]->clients =
            malloc(sizeof(client_t *) * args->max_clients_per_team);
        teams[i]->eggs = NULL;
        teams[i]->nb_eggs = 0;
    }
    teams[i] = NULL;
    return teams;
}
