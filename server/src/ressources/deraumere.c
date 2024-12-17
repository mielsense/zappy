/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** server.h
*/

#include "ai_commands.h"
#include "ui_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include "utils.h"
#include <unistd.h>

void update_deraumere(server_t *server, int deraumereQtt)
{
    int j = 0;
    int i = 0;

    while (deraumereQtt >= 1) {
        if (random_bit()) {
            if (random_bit()) {
                server->map[i][j].deraumereQtt += 1;
                deraumereQtt -= 1;
            }
        }
        j++;
        if (j == server->bin_args->width) {
            j = 0;
            i++;
        }
        if (i == server->bin_args->height)
            i = 0;
    }
}

void take_deraumere(command_data_t data, server_t *server)
{
    if (server->map[data.client->pos.y][data.client->pos.x].deraumereQtt < 1)
        return send_response(data.client, "ko\r\n");
    server->map[data.client->pos.y][data.client->pos.x].deraumereQtt -= 1;
    data.client->inventory->deraumere += 1;
    send_response(data.client, "ok\r\n");
    pgt(data, server);
}

void set_deraumere(command_data_t data, server_t *server)
{
    if (data.client->inventory->deraumere < 1)
        return send_response(data.client, "ko\r\n");
    data.client->inventory->deraumere -= 1;
    server->map[data.client->pos.y][data.client->pos.x].deraumereQtt += 1;
    send_response(data.client, "ok\r\n");
    pdr(data, server);
}
