/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** playerQtt
*/

#include "client.h"
#include "server.h"
#include <unistd.h>

int player_count(void *server_ptr, int x, int y)
{
    server_t *server = (server_t *)server_ptr;
    int players = 0;
    int i = 0;

    while (i < server->max_fd) {
        if (server->clients[i] != NULL && server->clients[i]->pos.x == x &&
            server->clients[i]->pos.y == y)
            players++;
        i++;
    }
    return players;
}
