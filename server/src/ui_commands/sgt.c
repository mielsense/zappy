/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** tna.c
*/

#include "response.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void sgt(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);

    sprintf(response, "sgt %f\r\n", server->bin_args->freq);
    send_response(data.client, response);
    free(response);
}
