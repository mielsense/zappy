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

void update_food(server_t *server, int foodQtt)
{
    int j = 0;
    int i = 0;

    while (foodQtt >= 1) {
        if (random_bit()) {
            if (random_bit()) {
                server->map[i][j].foodQtt += 1;
                foodQtt -= 1;
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

void take_food(command_data_t data, server_t *server)
{
    if (server->map[data.client->pos.y][data.client->pos.x].foodQtt >= 1) {
        server->map[data.client->pos.y][data.client->pos.x].foodQtt -= 1;
        data.client->inventory->food += 1;
        send_response(data.client, "ok\r\n");
        pgt(data, server);
    } else {
        send_response(data.client, "ko\r\n");
    }
}

void set_food(command_data_t data, server_t *server)
{
    if (data.client->inventory->food < 1)
        return send_response(data.client, "ko\r\n");
    data.client->inventory->food -= 1;
    server->map[data.client->pos.y][data.client->pos.x].foodQtt += 1;
    send_response(data.client, "ok\r\n");
    pdr(data, server);
}
