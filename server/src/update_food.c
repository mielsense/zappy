/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** update_food
*/

#include "response.h"
#include "server.h"

int has_126_units_passed(server_t *server)
{
    time_t current_time = time(NULL);
    double elapsed_time = difftime(current_time, server->food_clock);

    return (elapsed_time >= ((float)126 / server->bin_args->freq));
}

void player_starve(server_t *server, client_t *client)
{
    char *response = malloc(sizeof(char) * 1024);

    send_response(client, "dead\r\n");
    sprintf(response, "pdi %llu\r\n", client->id);
    send_to_all_graphical(server, response, client, true);
    free(response);
    client->is_dead = 1;
}

void consume_food(server_t *server)
{
    for (int i = 0; i <= server->max_fd; i++) {
        if (server->clients[i] == NULL || server->clients[i]->socket == -1 ||
            server->clients[i]->context != AI ||
            server->clients[i]->inventory == NULL ||
            server->clients[i]->is_dead)
            continue;
        server->clients[i]->inventory->food -= 1;
        if (server->clients[i]->inventory->food <= 0)
            player_starve(server, server->clients[i]);
    }
}

void update_engine_food(server_t *server, int fcall)
{
    if (!fcall || has_126_units_passed(server)) {
        consume_food(server);
        server->food_clock = time(NULL);
    }
}
