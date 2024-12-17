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
#include <string.h>
#include <unistd.h>

void tna(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    int i = 0;

    while (server->bin_args->teams_name[i] != NULL) {
        sprintf(response, "tna %s\n", server->bin_args->teams_name[i]);
        send_response(data.client, response);
        i++;
    }
    free(response);
}
