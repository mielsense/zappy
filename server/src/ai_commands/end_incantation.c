/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** end_incantation
*/

#include "ai_commands.h"
#include "client.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

void remove_ressources(server_t *server, int x, int y, int lvl)
{
    tile_t *tile = &server->map[y][x];

    if (lvl == 1) {
        tile->linemateQtt--;
    } else if (lvl == 2) {
        tile->linemateQtt--;
        tile->deraumereQtt--;
        tile->siburQtt--;
    } else if (lvl == 3) {
        tile->linemateQtt -= 2;
        tile->deraumereQtt--;
        tile->siburQtt--;
        tile->mendianeQtt--;
    } else if (lvl == 4) {
        tile->linemateQtt -= 2;
        tile->deraumereQtt--;
        tile->siburQtt -= 2;
        tile->phirasQtt--;
    } else if (lvl == 5) {
        tile->linemateQtt -= 4;
        tile->deraumereQtt--;
        tile->siburQtt -= 3;
        tile->phirasQtt--;
        tile->thystameQtt--;
    } else if (lvl == 6) {
        tile->linemateQtt -= 4;
        tile->deraumereQtt -= 2;
        tile->siburQtt--;
        tile->mendianeQtt -= 3;
        tile->phirasQtt--;
    } else if (lvl == 7) {
        tile->linemateQtt -= 6;
        tile->deraumereQtt--;
        tile->siburQtt -= 3;
        tile->mendianeQtt--;
        tile->phirasQtt -= 2;
    }
}

void incantation_success(command_data_t data, server_t *server)
{
    int x = data.client->pos.x;
    int y = data.client->pos.y;

    for (int i = 0; i <= server->max_fd; i++) {
        if (server->clients[i] != NULL && server->clients[i]->context == AI && 
            server->clients[i]->pos.x == x && server->clients[i]->pos.y == y &&
            server->clients[i]->lvl == data.client->lvl &&
            server->clients[i]->is_incanting == 1 &&
            server->clients[i]->context == AI) {
            server->clients[i]->lvl++;
            server->clients[i]->is_incanting = 0;
            dprintf(server->clients[i]->socket, "Current level: %d\r\n",
                server->clients[i]->lvl);
        }
        if (server->clients[i] != NULL && server->clients[i]->context == UI) {
            dprintf(server->clients[i]->socket, "pie %d %d ok\r\n", x, y);
        }
    }
    remove_ressources(server, x, y, data.client->lvl - 1);
}

void incantation_fail(command_data_t data, server_t *server)
{
    int x = data.client->pos.x;
    int y = data.client->pos.y;

    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i]->pos.x == x && server->clients[i]->pos.y == y &&
            server->clients[i]->lvl == data.client->lvl &&
            server->clients[i]->is_incanting == 1 &&
            server->clients[i]->context == AI) {
            server->clients[i]->is_incanting = 0;
            send_response(server->clients[i], "ko\r\n");
        }
        if (server->clients[i]->context == UI) {
            dprintf(server->clients[i]->socket, "pie %d %d ko\r\n", x, y);
        }
    }
    data.client->is_incanting = 0;
    send_response(data.client, "ko\r\n");
}

void end_incantation(command_data_t data, server_t *server)
{
    int check = check_incantation(data, server);

    if (check == 1 && data.client->is_dead == 0) {
        incantation_success(data, server);
    } else {
        incantation_fail(data, server);
    }
}
