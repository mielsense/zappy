/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** plv.c
*/

#include "response.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void plv(command_data_t data, server_t *server)
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
    sprintf(response, "plv #%llu %d\r\n", client->id, client->lvl);
    send_response(data.client, response);
    free(response);
}
