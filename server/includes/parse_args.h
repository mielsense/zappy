/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** server.h
*/

#pragma once
#include <dirent.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct parse_args {
    int port;
    int max_clients_per_team;
    float freq;
    int width;
    int height;
    char **teams_name;
};

typedef struct parse_args parse_args_t;

parse_args_t *parse_args(int argc, char **argv);
void display_args(parse_args_t *args);
