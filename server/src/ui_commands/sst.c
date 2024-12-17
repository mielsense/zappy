/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** tna.c
*/

#include "commands.h"
#include "response.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void sst(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    int new_freq;

    if (data.args == NULL || data.args[0] == NULL) {
        send_response(data.client, "KO\r\n");
        return;
    }
    new_freq = atoi(data.args[0]);
    server->bin_args->freq = new_freq;
    sprintf(response, "sst %d\r\n", new_freq);
    send_response(data.client, response);
    free(response);
}
