/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** server.c
*/

#include "client_context.h"
#include "client.h"
#include "parse_args.h"
#include "response.h"
#include "teams.h"
#include "ui_commands.h"
#include <stdio.h>

void spawn_ai(client_t *client, server_t *server, team_t *team)
{
    char *response = malloc(sizeof(char) * 1024);
    if (team->nb_eggs > 0 && team->eggs != NULL) {
        client->pos.x = team->eggs[team->nb_eggs - 1].pos.x;
        client->pos.y = team->eggs[team->nb_eggs - 1].pos.y;
        sprintf(response, "ebo #%llu\r\n", team->eggs[team->nb_eggs - 1].id);
        send_to_all_graphical(server, response, client, false);
        team->eggs = realloc(team->eggs, sizeof(egg_t) * (team->nb_eggs - 1));
        team->nb_eggs--;
    } else {
        client->pos.x = rand() % server->bin_args->width;
        client->pos.y = rand() % server->bin_args->height;
    }
    client->direction = rand() % 4 + 1;
    free(response);
}

int join_team_if_exists(client_t *client, server_t *server, char *team)
{
    int remaining_team_slots = 0;

    for (int i = 0; server->teams[i] != NULL; i++) {
        if (!strcmp(server->teams[i]->name, team)) {
            server->teams[i]->clients[server->teams[i]->nb_clients] = client;
            server->teams[i]->nb_clients++;
            remaining_team_slots =
                server->teams[i]->max_clients - server->teams[i]->nb_clients;
            client->team = strdup(team);
            spawn_ai(client, server, server->teams[i]);
            return remaining_team_slots;
        }
    }
    return 0;
}

void set_ai_context(
    client_t *client, server_t *server, int remaining_team_slots)
{
    char response[1024];

    client->context = AI;
    sprintf(response, "%d\r\n", remaining_team_slots);
    send_response(client, response);
    sprintf(response, "%i %i\r\n", server->bin_args->width,
        server->bin_args->height);
    send_response(client, response);
    pnw(client, server);
    printf("[LOG] AI auth on socket %d\n", client->socket);
}

void set_graphical_context(client_t *client)
{
    client->context = UI;
    send_response(client, "OK\r\n");
    printf("[LOG] GRAPHIC auth on socket %d\n", client->socket);
}

bool set_client_context(client_t *client, void *server_ptr, char *context)
{
    int remaining_team_slots = 0;
    char *parsed_context = strdup(context);
    server_t *server = (server_t *)server_ptr;

    strtok(parsed_context, "\n");
    if (!strcmp(parsed_context, "GRAPHIC"))
        set_graphical_context(client);
    else {
        remaining_team_slots =
            join_team_if_exists(client, server, parsed_context);
        if (remaining_team_slots < 1)
            return false;
        set_ai_context(client, server, remaining_team_slots);
    }
    return true;
}
