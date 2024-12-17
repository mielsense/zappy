/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** tile.h
*/

#pragma once
#include "client.h"
#include <dirent.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct tile {
    int foodQtt;
    int linemateQtt;
    int deraumereQtt;
    int siburQtt;
    int mendianeQtt;
    int phirasQtt;
    int thystameQtt;
    bool has_player;
};

typedef struct tile tile_t;

tile_t **init_map(int width, int height);
tile_t calculate_required_ressources(int width, int height);
