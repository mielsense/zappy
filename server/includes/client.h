/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** client.h
*/

#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#define TIMEOUT_SEC 180
#define CONTEXT_COUNT 4

struct pos {
    int x;
    int y;
};
typedef struct pos pos_t;

struct inventory {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};
typedef struct inventory inventory_t;

enum direction {
    TOP = 1,
    BOTTOM = 3,
    LEFT = 4,
    RIGHT = 2
};
typedef enum direction direction_t;

enum client_context {
    NONE,
    AI,
    UI,
};
typedef enum client_context client_context_t;

struct client {
    int socket;
    int lvl;
    client_context_t context;
    inventory_t *inventory;
    char *username;
    char *team;
    uint64_t id;
    int connection_attempts;
    pos_t pos;
    direction_t direction;
    int is_incanting;
    int is_dead;
};
typedef struct client client_t;

client_t *init_client(int socket);
client_t *get_client_by_id(void *server_ptr, int id);
