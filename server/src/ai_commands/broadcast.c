/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast.c
*/

#include "client.h"
#include "response.h"
#include "utils.h"
#include <stdio.h>

// TODO: Refactor this file to have max 5 functions
int get_tile_from_top(int diff_x, int diff_y)
{
    if (diff_x == 0 && diff_y == 1)
        return 1;
    if (diff_x == 1 && diff_y == 1)
        return 2;
    if (diff_x == 1 && diff_y == 0)
        return 3;
    if (diff_x == 1 && diff_y == -1)
        return 4;
    if (diff_x == 0 && diff_y == -1)
        return 5;
    if (diff_x == -1 && diff_y == -1)
        return 6;
    if (diff_x == -1 && diff_y == 0)
        return 7;
    if (diff_x == -1 && diff_y == 1)
        return 8;
    return 0;
}

int get_tile_from_right(int diff_x, int diff_y)
{
    if (diff_x == 1 && diff_y == 0)
        return 1;
    if (diff_x == 1 && diff_y == 1)
        return 2;
    if (diff_x == 0 && diff_y == 1)
        return 3;
    if (diff_x == -1 && diff_y == 1)
        return 4;
    if (diff_x == -1 && diff_y == 0)
        return 5;
    if (diff_x == -1 && diff_y == -1)
        return 6;
    if (diff_x == 0 && diff_y == -1)
        return 7;
    if (diff_x == 1 && diff_y == -1)
        return 8;
    return 0;
}

int get_tile_from_bottom(int diff_x, int diff_y)
{
    if (diff_x == 0 && diff_y == -1)
        return 1;
    if (diff_x == -1 && diff_y == -1)
        return 2;
    if (diff_x == -1 && diff_y == 0)
        return 3;
    if (diff_x == -1 && diff_y == 1)
        return 4;
    if (diff_x == 0 && diff_y == 1)
        return 5;
    if (diff_x == 1 && diff_y == 1)
        return 6;
    if (diff_x == 1 && diff_y == 0)
        return 7;
    if (diff_x == 1 && diff_y == -1)
        return 8;
    return 0;
}

int get_tile_from_left(int diff_x, int diff_y)
{
    if (diff_x == -1 && diff_y == 0)
        return 1;
    if (diff_x == -1 && diff_y == -1)
        return 2;
    if (diff_x == 0 && diff_y == -1)
        return 3;
    if (diff_x == 1 && diff_y == -1)
        return 4;
    if (diff_x == 1 && diff_y == 0)
        return 5;
    if (diff_x == 1 && diff_y == 1)
        return 6;
    if (diff_x == 0 && diff_y == 1)
        return 7;
    if (diff_x == -1 && diff_y == 1)
        return 8;
    return 0;
}

int calculate_sound_direction(client_t *emitter, client_t *receiver)
{
    int diff_x = normalize(receiver->pos.x - emitter->pos.x);
    int diff_y = normalize(receiver->pos.y - emitter->pos.y);

    switch (receiver->direction) {
    case TOP:
        return get_tile_from_top(diff_x, diff_y);
    case RIGHT:
        return get_tile_from_right(diff_x, diff_y);
    case BOTTOM:
        return get_tile_from_bottom(diff_x, diff_y);
    case LEFT:
        return get_tile_from_left(diff_x, diff_y);
    default:
        return 0;
    }
}

void broadcast(command_data_t data, server_t *server)
{
    char response[1024];
    direction_t direction;

    sprintf(response, "pbc #%llu %s\r\n", data.client->id, data.args[1]);
    send_to_all_graphical(server, response, data.client, true);
    for (int i = 0; i < server->max_fd; i++) {
        direction = calculate_sound_direction(data.client, server->clients[i]);
        sprintf(response, "message %d, %s\r\n", direction, data.args[1]);
        send_response(server->clients[i], response);
    }
    send_response(data.client, "OK\r\n");
}
