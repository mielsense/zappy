/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right
*/

#include "ai_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

void right(command_data_t data, server_t *server)
{
    if (data.client->direction == TOP)
        data.client->direction = RIGHT;
    else if (data.client->direction == RIGHT)
        data.client->direction = BOTTOM;
    else if (data.client->direction == BOTTOM)
        data.client->direction = LEFT;
    else if (data.client->direction == LEFT)
        data.client->direction = TOP;
    send_response(data.client, "ok\r\n");
}
