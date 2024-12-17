/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** main.c
*/

#include "parse_args.h"

char **get_teams(char **argv, int argc, int i)
{
    char **teams = malloc(sizeof(char *) * (argc - i + 1));
    int j = 0;

    while (i + j + 1 < argc && argv[i + j + 1][0] != '-') {
        teams[j] = strdup(argv[i + j + 1]);
        j++;
    }
    teams[j] = NULL;
    return teams;
}

parse_args_t *init_parse_args(void)
{
    parse_args_t *args = malloc(sizeof(parse_args_t));

    args->port = 0;
    args->width = 0;
    args->height = 0;
    args->teams_name = NULL;
    args->max_clients_per_team = 0;
    args->freq = 100;
    return args;
}

void display_args(parse_args_t *args)
{
    printf("port: %d\n", args->port);
    printf("width: %d\n", args->width);
    printf("height: %d\n", args->height);
    printf("maxClients: %d\n", args->max_clients_per_team);
    printf("freq: %f\n", args->freq);
    if (args->teams_name == NULL)
        return;
    for (int i = 0; args->teams_name[i] != NULL; i++)
        printf("team: %s\n", args->teams_name[i]);
}

void error_handling(parse_args_t *args)
{
    if (args->port <= 0) {
        fprintf(stderr, "Invalid port number\n");
        exit(84);
    }
    if (args->width <= 0) {
        fprintf(stderr, "Invalid width\n");
        exit(84);
    }
    if (args->height <= 0) {
        fprintf(stderr, "Invalid height\n");
        exit(84);
    }
    if (args->max_clients_per_team <= 0) {
        fprintf(stderr, "Invalid maxClients\n");
        exit(84);
    }
    if (args->freq <= 0)
        args->freq = 100;
}

parse_args_t *parse_args(int argc, char **argv)
{
    parse_args_t *args = init_parse_args();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
            args->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && i + 1 < argc)
            args->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && i + 1 < argc)
            args->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
            args->teams_name = get_teams(argv, argc, i);
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
            args->max_clients_per_team = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            args->freq = strtof(argv[i + 1], NULL);
    }
    error_handling(args);
    return args;
}
