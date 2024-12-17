/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** pnw.c
*/

#include "response.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void pnw(client_t *client, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    int orientation = 0;

    sprintf(response, "pnw #%llu %d %d %d %d %s\r\n", client->id,
        client->pos.x, client->pos.y, orientation, client->lvl, client->team);
    send_to_all_graphical(server, response, client, false);
    free(response);
}
