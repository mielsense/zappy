/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** take.c
*/

#include "ai_commands.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

void take(command_data_t data, server_t *server)
{
    if (data.args[0] == NULL)
        return send_response(data.client, "ko\r\n");
    if (strncmp(data.args[0], "food", 4) == 0)
        return take_food(data, server);
    if (strncmp(data.args[0], "linemate", 8) == 0)
        return take_linemate(data, server);
    if (strncmp(data.args[0], "deraumere", 9) == 0)
        return take_deraumere(data, server);
    if (strncmp(data.args[0], "sibur", 5) == 0)
        return take_sibur(data, server);
    if (strncmp(data.args[0], "mendiane", 8) == 0)
        return take_mendiane(data, server);
    if (strncmp(data.args[0], "phiras", 6) == 0)
        return take_phiras(data, server);
    if (strncmp(data.args[0], "thystame", 8) == 0)
        return take_thystame(data, server);
    return send_response(data.client, "ko\r\n");
}
