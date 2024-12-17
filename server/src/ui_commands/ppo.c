/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** ppo.c
*/

#include "response.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_orientation(int direction)
{
    switch (direction) {
    case TOP:
        return 1;
    case RIGHT:
        return 2;
    case BOTTOM:
        return 3;
    case LEFT:
        return 4;
    }
    return 0;
}

void ppo(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    int orientation = 0;
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
    orientation = get_orientation(client->direction);
    sprintf(response, "ppo #%llu %d %d %d\r\n", client->id, client->pos.x,
        client->pos.y, orientation);
    send_response(data.client, response);
    free(response);
}
