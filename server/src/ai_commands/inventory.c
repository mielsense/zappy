/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include "ai_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void inventory(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);

    sprintf(response,
        "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras "
        "%d, thystame %d]\r\n",
        (int)data.client->inventory->food,
        (int)data.client->inventory->linemate,
        (int)data.client->inventory->deraumere,
        (int)data.client->inventory->sibur,
        (int)data.client->inventory->mendiane,
        (int)data.client->inventory->phiras,
        (int)data.client->inventory->thystame);
    send_response(data.client, response);
    free(response);
}
