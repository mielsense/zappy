/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** team.h
*/

#pragma once
#include "client.h"
#include "parse_args.h"
#include "teams.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

bool set_client_context(client_t *client, void *server_ptr, char *team);
