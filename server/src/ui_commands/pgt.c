/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** pgt
*/

#include "client.h"
#include "response.h"
#include "server.h"
#include "ui_commands.h"
#include <unistd.h>

void pgt(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);

    sprintf(response, "pgt #%llu %d\r\n", data.client->id,
        data.client->pos.x * data.client->pos.y);
    send_to_all_graphical(server, response, data.client, false);
    free(response);
}
