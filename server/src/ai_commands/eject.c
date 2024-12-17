/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include "client.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

client_t **find_clients_to_eject(pos_t pos, server_t *server)
{
    client_t **clients = malloc(sizeof(client_t *) * server->max_fd);
    int nb_clients = 0;

    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i]->pos.x == pos.x &&
            server->clients[i]->pos.y == pos.y) {
            clients[nb_clients] = server->clients[i];
            nb_clients++;
        }
    }
    clients = realloc(clients, sizeof(client_t *) * (nb_clients + 1));
    clients[nb_clients] = NULL;
    return clients;
}

void eject_client(client_t *client, direction_t direction, server_t *server)
{
    pos_t new_pos = client->pos;

    switch (direction) {
    case TOP:
        new_pos.y = (new_pos.y - 1) % server->bin_args->height;
        break;
    case RIGHT:
        new_pos.x = (new_pos.x + 1) % server->bin_args->width;
        break;
    case BOTTOM:
        new_pos.y = (new_pos.y + 1) % server->bin_args->height;
        break;
    case LEFT:
        new_pos.x = (new_pos.x - 1) % server->bin_args->width;
        break;
    }
    client->pos = new_pos;
    server->map[new_pos.y][new_pos.x].has_player = true;
}

void eject(command_data_t data, server_t *server)
{
    client_t **clients = find_clients_to_eject(data.client->pos, server);
    char response[1024];

    for (int i = 0; clients[i] != NULL; i++) {
        eject_client(clients[i], data.client->direction, server);
        sprintf(
            response, "eject: %d %d\n", clients[i]->pos.x, clients[i]->pos.y);
        send_response(clients[i], response);
    }
}
