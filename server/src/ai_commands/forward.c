/*
** EPITECH PROJECT, 2024
** forward
** File description:
** forward.c
*/

#include "ai_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

pos_t calculate_new_position(client_t *client, server_t *server)
{
    switch (client->direction) {
    case TOP:
        return (pos_t){
            .x = client->pos.x,
            .y = (client->pos.y - 1 + server->bin_args->height) % server->bin_args->height
        };
    case RIGHT:
        return (pos_t){
            .x = (client->pos.x + 1) % server->bin_args->width,
            .y = client->pos.y
        };
    case LEFT:
        if (client->pos.x > 0)
            return (pos_t){
                .x = (client->pos.x - 1 + server->bin_args->width) % server->bin_args->width,
                .y = client->pos.y
            };
    case BOTTOM:
        return (pos_t){
            .x = client->pos.x,
            .y = (client->pos.y + 1) % server->bin_args->height
        };
    default:
        return client->pos;
    }
}

void forward(command_data_t data, server_t *server)
{
    pos_t new_pos = calculate_new_position(data.client, server);
    server->map[data.client->pos.y][data.client->pos.x].has_player = false;
    server->map[new_pos.y][new_pos.x].has_player = true;
    data.client->pos = new_pos;
    send_response(data.client, "ok\r\n");
}
