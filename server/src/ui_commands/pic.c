/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** pic
*/

#include "client.h"
#include "response.h"
#include "server.h"
#include "ui_commands.h"
#include <string.h>
#include <unistd.h>

void pic(command_data_t data, server_t *server, int required_players,
    client_t **list)
{
    char *response = malloc(sizeof(char) * 1024);
    char *temp = malloc(sizeof(char) * 1024);

    sprintf(response, "pic %d %d %d", data.client->pos.x, data.client->pos.y,
        data.client->lvl);
    required_players--;
    for (int i = 0; required_players; i++) {
        if (list[i]->id != data.client->id) {
            strcat(response, " ");
            sprintf(temp, "%llu", list[i]->id);
            strcat(response, temp);
            required_players--;
        }
    }
    strcat(response, "\r\n");
    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i]->context == UI)
            send_response(server->clients[i], response);
    }
    free(response);
    free(temp);
}
