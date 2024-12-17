/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** mct.c
*/

#include "response.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void mct(command_data_t data, server_t *server)
{
    char *response =
        malloc(1024 * server->bin_args->height * server->bin_args->width);
    char line[1024];

    response[0] = '\0';
    for (int y = 0; y < server->bin_args->height; y++) {
        for (int x = 0; x < server->bin_args->width; x++) {
            snprintf(line, sizeof(line), "bct %d %d %d %d %d %d %d %d %d\n", x,
                y, server->map[y][x].foodQtt, server->map[y][x].linemateQtt,
                server->map[y][x].deraumereQtt, server->map[y][x].siburQtt,
                server->map[y][x].mendianeQtt, server->map[y][x].phirasQtt,
                server->map[y][x].thystameQtt);
            strcat(response, line);
        }
    }
    strcat(response, "\r\n");
    send_response(data.client, response);
    free(response);
}
