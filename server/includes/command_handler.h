/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** command_data.h
*/

#pragma once
#include "client.h"

typedef struct command_data command_data_t;
typedef void (*command_handler_t)(command_data_t, void *);

struct command_data {
    char *name;
    char **args;
    int duration;
    client_t *client;
    command_handler_t handler;
    time_t cast_time;
    pos_t cast_pos;
};

void handle_commands(void *server_ptr);
