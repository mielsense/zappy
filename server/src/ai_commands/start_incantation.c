/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** incantation
*/

#include "ai_commands.h"
#include "client.h"
#include "commands.h"
#include "response.h"
#include "server.h"
#include "ui_commands.h"
#include <stdio.h>
#include <unistd.h>

client_t **get_list_of_client_same_lvl(server_t *server, int x, int y, int lvl)
{
    client_t **list = malloc(sizeof(client_t *) * 7);
    int j = 0;

    for (int i = 0; i < server->max_fd; i++) {
        if (server->clients[i] != NULL && server->clients[i]->context == AI && server->clients[i]->pos.x == x && server->clients[i]->pos.y == y &&
            server->clients[i]->lvl == lvl) {
            list[j] = server->clients[i];
            j++;
        }
    }
    list[j] = NULL;
    return list;
}

int player_of_same_lvl(server_t *server, int x, int y, int lvl)
{
    int count = 0;
    for (int i = 0; i <= server->max_fd; i++) {
        if (server->clients[i] != NULL && server->clients[i]->context == AI && server->clients[i]->pos.x == x && server->clients[i]->pos.y == y &&
            server->clients[i]->lvl == lvl) {
            count++;
        }
    }
    return count;
}

int check_lvl_one(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 1 && player_count >= 1)
        return 1;
    return 0;
}

int check_lvl_two(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 1 && tile.deraumereQtt >= 1 &&
        tile.siburQtt >= 1 && player_count >= 2)
        return 1;
    return 0;
}

int check_lvl_three(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 2 && tile.siburQtt >= 1 && tile.phirasQtt >= 2 &&
        player_count >= 2)
        return 1;
    return 0;
}

int check_lvl_four(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 1 && tile.deraumereQtt >= 1 &&
        tile.siburQtt >= 2 && tile.phirasQtt >= 1 && player_count >= 4)
        return 1;
    return 0;
}

int check_lvl_five(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 1 && tile.deraumereQtt >= 2 &&
        tile.siburQtt >= 1 && tile.mendianeQtt >= 3 && player_count >= 4)
        return 1;
    return 0;
}

int check_lvl_six(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 1 && tile.deraumereQtt >= 2 &&
        tile.siburQtt >= 3 && tile.phirasQtt >= 1 && player_count >= 6)
        return 1;
    return 0;
}

int check_lvl_seven(tile_t tile, int player_count)
{
    if (tile.linemateQtt >= 2 && tile.deraumereQtt >= 2 &&
        tile.siburQtt >= 2 && tile.mendianeQtt >= 2 && tile.phirasQtt >= 2 &&
        tile.thystameQtt >= 1 && player_count >= 6)
        return 1;
    return 0;
}

int check_incantation(command_data_t data, server_t *server)
{
    int player_count = player_of_same_lvl(
        server, data.client->pos.x, data.client->pos.y, data.client->lvl);
    tile_t tile = server->map[data.client->pos.y][data.client->pos.x];

    if (data.client->lvl == 1)
        return check_lvl_one(tile, player_count);
    if (data.client->lvl == 2)
        return check_lvl_two(tile, player_count);
    if (data.client->lvl == 3)
        return check_lvl_three(tile, player_count);
    if (data.client->lvl == 4)
        return check_lvl_four(tile, player_count);
    if (data.client->lvl == 5)
        return check_lvl_five(tile, player_count);
    if (data.client->lvl == 6)
        return check_lvl_six(tile, player_count);
    if (data.client->lvl == 7)
        return check_lvl_seven(tile, player_count);
    return 0;
}

int required_players(int lvl)
{
    if (lvl == 1)
        return 1;
    if (lvl == 2)
        return 2;
    if (lvl == 3)
        return 2;
    if (lvl == 4)
        return 4;
    if (lvl == 5)
        return 4;
    if (lvl == 6)
        return 6;
    if (lvl == 7)
        return 6;
    return 0;
}

void launch_incantation(command_data_t data, server_t *server, client_t **list)
{
    int required = required_players(data.client->lvl) - 1;
    int required_save = required;
    client_t *client = data.client;

    client->is_incanting = 1;
    if (required == 0)
        return;
    for (int i = 0; i < required; i++) {
        if (list[i]->socket == client->socket) {
            required++;
            continue;
        }
        send_response(list[i], "Elevation underway\r\n");
        list[i]->is_incanting = 1;
    }
    pic(data, server, required_save, list);
}

void start_incantation(command_data_t data, server_t *server)
{
    client_t **list = get_list_of_client_same_lvl(
        server, data.client->pos.x, data.client->pos.y, data.client->lvl);

    if (check_incantation(data, server) == 0) {
        send_response(data.client, "ko\r\n");
        return;
    }
    data.args = NULL;
    data.name = "pic";
    data.duration = 300;
    data.handler = (command_handler_t)end_incantation;
    launch_incantation(data, server, list);
    append_node(&server->commands, data);
    send_response(data.client, "Elevation underway\r\n");
}
