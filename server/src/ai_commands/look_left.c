/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "ai_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include <string.h>
#include <unistd.h>

void look_left(client_t *client, server_t *server)
{
    char *response = malloc(sizeof(char) * 4096);
    char *tmp;
    int row = 0;
    int x = 0;
    int y = 0;

    strcat(response, "[");
    while (row <= client->lvl) {
        y = client->pos.y - row;
        x = client->pos.x - row;
        while (y <= client->pos.y + row) {
            tmp = tile_content(server->map, server,
                x % server->bin_args->width, y % server->bin_args->height);
            strcat(response, tmp);
            free(tmp);
            if (y + 1 <= client->pos.y + row)
                strcat(response, ",");
            y++;
        }
        if (row + 1 <= client->lvl)
            strcat(response, ",");
        row++;
    }
    strcat(response, "]\r\n");
    send_response(client, response);
    free(response);
}
