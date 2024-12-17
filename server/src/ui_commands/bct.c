/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** bct.c
*/

#include "parse_args.h"
#include "response.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void display_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        printf("%s\n", array[i]);
}

void bct(command_data_t data, server_t *server)
{
    int x;
    int y;
    char *response = malloc(sizeof(char) * 1024);

    if (data.args == NULL || data.args[0] == NULL || data.args[1] == NULL) {
        free(response);
        return send_response(data.client, "KO invalid arguments\r\n");
    }
    x = atoi(data.args[0]);
    y = atoi(data.args[1]);
    if (x < 0 || x >= server->bin_args->width || y < 0 ||
        y >= server->bin_args->height)
        return send_response(data.client, "ko invalid arguments\n");
    sprintf(response, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        server->map[x][y].foodQtt, server->map[x][y].linemateQtt,
        server->map[x][y].deraumereQtt, server->map[x][y].siburQtt,
        server->map[x][y].mendianeQtt, server->map[x][y].phirasQtt,
        server->map[x][y].thystameQtt);
    send_response(data.client, response);
    free(response);
}
