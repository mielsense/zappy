/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** client.c
*/

#include "client.h"
#include "requests.h"
#include "response.h"
#include "server.h"
#include <stdlib.h>

int handle_client(client_t *client, server_t *server)
{
    int nbytes;
    char buffer[BUFFER_SIZE];

    nbytes = read(client->socket, buffer, sizeof(buffer));
    if (nbytes <= 0)
        return 0;
    buffer[nbytes] = '\0';
    strtok(buffer, "\r\n");
    if (strlen(buffer) == 0)
        return 1;
    if (client->context == NONE && client->connection_attempts < 10) {
        if (set_client_context(client, server, buffer))
            return 1;
        else {
            printf("[LOG] AI auth failed on socket %d\n", client->socket);
            send_response(client, "ko\r\n");
            client->connection_attempts++;
            return 1;
        }
    }
    handle_client_requests(client, buffer, server);
    return 1;
}

client_t *get_client_by_id(void *server_ptr, int id)
{
    server_t *server = (server_t *)server_ptr;

    for (int i = 0; i <= server->max_fd; i++) {
        if (server->clients[i] == NULL)
            continue;
        if (server->clients[i]->id == id && server->clients[i]->context == AI)
            return server->clients[i];
    }
    return NULL;
}
