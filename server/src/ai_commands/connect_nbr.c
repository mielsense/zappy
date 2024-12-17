/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** connect_nbr
*/

#include "response.h"
#include "server.h"
#include <unistd.h>

void connect_nbr(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    int team_slots = server->bin_args->max_clients_per_team;

    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i] != NULL && server->clients[i]->context == AI
        && strcmp(server->clients[i]->team, data.client->team) == 0)
            team_slots--;
    }
    sprintf(response, "%d\r\n", team_slots);
    send_response(data.client, response);
    free(response);
}
