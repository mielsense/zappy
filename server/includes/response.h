/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** server.h
*/

#pragma once

#include "server.h"
#include <stdbool.h>

void send_response(client_t *client, const char *response);
void send_to_all(server_t *server, char *response);
void send_to_all_ai(
    server_t *server, char *response, client_t *client, bool ignore_self);
void send_to_all_graphical(
    server_t *server, char *response, client_t *client, bool ignore_self);
void send_to_all_others(server_t *server, client_t *client, char *response);
