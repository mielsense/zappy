/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** server.h
*/

#pragma once
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 1024
#include "client.h"
#include "client_context.h"
#include "commands.h"
#include "parse_args.h"
#include "tile.h"
#include <dirent.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct server {
    int socket;
    fd_set master;
    fd_set temp;
    int current_fd;
    int max_fd;
    parse_args_t *bin_args;
    client_t **clients;
    tile_t **map;
    tile_t ressourcesMax;
    time_t ressource_clock;
    time_t food_clock;
    team_t **teams;
    node_t *commands;
    struct timeval timeval;
};
typedef struct server server_t;

void start_server(parse_args_t *args);
void update_resources(server_t *server, int is_first_call);
void update_engine_food(server_t *server, int fcall);
