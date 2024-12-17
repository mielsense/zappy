/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** commands.h
*/

#pragma once
#include "client.h"
#include "server.h"
#include <dirent.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    char *name;
    int duration;
    command_handler_t handler;
    enum client_context type;
} request_mapping_t;

void handle_client_requests(client_t *client, char *buffer, server_t *server);
