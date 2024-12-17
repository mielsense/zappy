/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** response.c
*/

#include "server.h"
#include <stdbool.h>

void send_response(client_t *client, const char *response)
{
    if (client)
        write(client->socket, response, strlen(response));
}

void send_to_all(server_t *server, char *response)
{
    for (int i = 0; i <= server->max_fd; i++) {
        if (server->clients[i] && server->clients[i]->context != NONE)
            send_response(server->clients[i], response);
    }
}

void send_to_all_ai(
    server_t *server, char *response, client_t *client, bool ignore_self)
{
    for (int i = 0; i <= server->max_fd; i++) {
        if (!server->clients[i])
            continue;
        if (ignore_self && server->clients[i] == client)
            continue;
        if (server->clients[i] && server->clients[i]->context == AI)
            send_response(server->clients[i], response);
    }
}

void send_to_all_graphical(
    server_t *server, char *response, client_t *client, bool ignore_self)
{
    for (int i = 0; i <= server->max_fd; i++) {
        if (!server->clients[i])
            continue;
        if (ignore_self && server->clients[i] == client)
            continue;
        if (server->clients[i] && server->clients[i]->context == UI) {
            send_response(server->clients[i], response);
        }
    }
}
