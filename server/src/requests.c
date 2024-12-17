/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** commands.c
*/

#include "requests.h"
#include "ai_commands.h"
#include "command_handler.h"
#include "commands.h"
#include "response.h"
#include "server.h"
#include "ui_commands.h"
#include "utils.h"

request_mapping_t request_mapping[] = {
    {"msz", 0, (command_handler_t)msz, UI},
    {"bct", 0, (command_handler_t)bct, UI},
    {"mct", 0, (command_handler_t)mct, UI},
    {"tna", 0, (command_handler_t)tna, UI},
    {"ppo", 0, (command_handler_t)ppo, UI},
    {"plv", 0, (command_handler_t)plv, UI},
    {"pin", 0, (command_handler_t)pin, UI},
    {"sgt", 0, (command_handler_t)sgt, UI},
    {"sst", 0, (command_handler_t)sst, UI},
    {"Look", 7, (command_handler_t)look, AI},
    {"Forward", 7, (command_handler_t)forward, AI},
    {"Right", 7, (command_handler_t)right, AI},
    {"Left", 7, (command_handler_t)left, AI},
    {"Inventory", 1, (command_handler_t)inventory, AI},
    {"Broadcast", 7, (command_handler_t)broadcast, AI},
    {"Take", 7, (command_handler_t)take, AI},
    {"Set", 7, (command_handler_t)set, AI},
    {"Fork", 42, (command_handler_t)ai_fork, AI},
    {"Incantation", 0, (command_handler_t)start_incantation, AI},
    {"Connect_nbr", 0, (command_handler_t)connect_nbr, AI},
    {"Eject", 7, (command_handler_t)eject, AI},
    {NULL, 0, NULL},
};

command_data_t create_command_data(
    int command_index, char *buffer, client_t *client)
{
    command_data_t data;
    char *argument;

    argument = buffer + strlen(request_mapping[command_index].name) + 1;
    argument[strcspn(argument, "\r\n")] = '\0';
    data.name = request_mapping[command_index].name;
    data.args = split(argument, ' ');
    data.duration = request_mapping[command_index].duration;
    data.handler = request_mapping[command_index].handler;
    data.client = client;
    data.cast_time = time(NULL);
    data.cast_pos = client->pos;
    return data;
}

int client_can_request(
    request_mapping_t request, client_t *client, char *buffer)
{
    if (strncmp(buffer, request.name, strlen(request.name)) == 0) {
        if (request.type == client->context)
            return 1;
        return 0;
    }
    return 0;
}

void handle_client_requests(client_t *client, char *buffer, server_t *server)
{
    command_data_t data;
    if (client->context == AI && client->is_incanting == 1)
        return;
    if (client->context == AI && client->is_dead == 1)
        return;
    for (int i = 0; request_mapping[i].name != NULL; i++) {
        if (client_can_request(request_mapping[i], client, buffer)) {
            data = create_command_data(i, buffer, client);
            append_node(&server->commands, data);
            return;
        }
    }
    if (client->context == UI)
        send_response(client, "suc\r\n");
    send_response(client, "ko\r\n");
}
