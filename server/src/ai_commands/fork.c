/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** end_incantation
*/

#include "ai_commands.h"
#include "command_handler.h"
#include "commands.h"
#include "response.h"
#include "server.h"
#include "teams.h"

void delay_end_fork(command_data_t data, server_t *server)
{
    command_data_t new_data;

    new_data.args = NULL;
    new_data.duration = 42;
    new_data.name = "enw";
    new_data.handler = (command_handler_t)ai_fork_finished;
    new_data.client = data.client;
    new_data.cast_time = data.cast_time;
    new_data.cast_pos = data.client->pos;
    append_node(&server->commands, new_data);
}

void ai_fork_finished(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);
    team_t *team = get_team_by_name(server, data.client->team);
    egg_t new_egg = add_new_egg_to_team(team, data.cast_pos);

    sprintf(response, "enw #%llu #%llu %d %d\r\n", new_egg.id, data.client->id,
        data.cast_pos.x, data.cast_pos.y);
    send_to_all_graphical(server, response, data.client, true);
    send_response(data.client, "OK\r\n");
    free(response);
}

void ai_fork(command_data_t data, server_t *server)
{
    char *response = malloc(sizeof(char) * 1024);

    delay_end_fork(data, server);
    sprintf(response, "pfk #%llu\n", data.client->id);
    send_to_all_graphical(server, response, data.client, false);
    free(response);
}
