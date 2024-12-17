/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look.c
*/

#include "ai_commands.h"
#include "client.h"
#include "server.h"
#include <string.h>
#include <unistd.h>

int is_there_other_players(server_t *server, int x, int y)
{
    int count = 0;

    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i] != NULL && server->clients[i]->context == AI && server->clients[i]->pos.x == x && server->clients[i]->pos.y == y)
            count++;
    }
    if (count > 1)
        return 1;
    return 0;
}

char *tile_content(tile_t **map, server_t *server, int x, int y) {
    char *response = malloc(sizeof(char) * 1024);
    int itemCount = 0;

    response[0] = '\0';
    if (server->bin_args->height <= y || server->bin_args->width <= x || x < 0 || y < 0) {
        free(response);
        return strdup("");
    }
    if (map[y][x].foodQtt > 0) { strcat(response, " food"); itemCount++; }
    if (map[y][x].linemateQtt > 0) { strcat(response, " linemate"); itemCount++; }
    if (map[y][x].deraumereQtt > 0) { strcat(response, " deraumere"); itemCount++; }
    if (map[y][x].siburQtt > 0) { strcat(response, " sibur"); itemCount++; }
    if (map[y][x].mendianeQtt > 0) { strcat(response, " mendiane"); itemCount++; }
    if (map[y][x].phirasQtt > 0) { strcat(response, " phiras"); itemCount++; }
    if (map[y][x].thystameQtt > 0) { strcat(response, " thystame"); itemCount++; }
    if (is_there_other_players(server, x, y)) { strcat(response, " player"); itemCount++; }
    if (itemCount == 0) {
        free(response);
        return strdup("");
    }
    if (itemCount == 1) {
        memmove(response, response + 1, strlen(response));
    }
    return response;
}

void look(command_data_t data, server_t *server)
{
    if (data.client->direction == TOP)
        return look_top(data.client, server);
    if (data.client->direction == BOTTOM)
        return look_bottom(data.client, server);
    if (data.client->direction == LEFT)
        return look_left(data.client, server);
    if (data.client->direction == RIGHT)
        return look_right(data.client, server);
}
