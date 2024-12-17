/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** set
*/

#include "ai_commands.h"
#include "response.h"
#include "server.h"
#include <unistd.h>

void set(command_data_t data, server_t *server)
{
    if (data.args[0] == NULL)
        return send_response(data.client, "ko\r\n");
    if (strncmp(data.args[0], "food", 4) == 0)
        return set_food(data, server);
    if (strncmp(data.args[0], "linemate", 8) == 0)
        return set_linemate(data, server);
    if (strncmp(data.args[0], "deraumere", 9) == 0)
        return set_deraumere(data, server);
    if (strncmp(data.args[0], "sibur", 5) == 0)
        return set_sibur(data, server);
    if (strncmp(data.args[0], "mendiane", 8) == 0)
        return set_mendiane(data, server);
    if (strncmp(data.args[0], "phiras", 6) == 0)
        return set_phiras(data, server);
    if (strncmp(data.args[0], "thystame", 8) == 0)
        return set_thystame(data, server);
    return send_response(data.client, "ko\r\n");
}
