/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** pin.c
*/

#include "client.h"
#include "response.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pin(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    client_t *client;
    int client_id;

    if (data.args == NULL)
        return send_response(data.client, "KO\r\n");
    client_id = get_player_id(data.args[0]);
    if (client_id == -1)
        return send_response(data.client, "KO\r\n");
    client = get_client_by_id(server, client_id);
    if (!client)
        return send_response(data.client, "KO\r\n");
    sprintf(response, "pin #%llu %d %d %d %d %d %d %d %d %d\r\n", client->id,
        client->pos.x, client->pos.y, (int)client->inventory->food,
        (int)client->inventory->linemate, (int)client->inventory->deraumere,
        (int)client->inventory->sibur, (int)client->inventory->mendiane,
        (int)client->inventory->phiras, (int)client->inventory->thystame);
    send_response(data.client, response);
    free(response);
}
