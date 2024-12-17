/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** commands.c
*/

#include "client.h"
#include <stdint.h>

inventory_t *init_inventory(void)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));

    inventory->food = 10;
    inventory->linemate = 0;
    inventory->deraumere = 0;
    inventory->sibur = 0;
    inventory->mendiane = 0;
    inventory->phiras = 0;
    inventory->thystame = 0;
    return inventory;
}

uint64_t set_client_id(void)
{
    static uint64_t id = 0;

    id++;
    return id;
}

client_t *init_client(int socket)
{
    client_t *client = malloc(sizeof(client_t));

    client->socket = socket;
    client->username = NULL;
    client->context = NONE;
    client->lvl = 1;
    client->inventory = init_inventory();
    client->id = set_client_id();
    client->team = NULL;
    client->connection_attempts = 0;
    client->pos = (pos_t){0, 0};
    client->direction = TOP;
    client->is_incanting = 0;
    client->is_dead = 0;
    return client;
}
