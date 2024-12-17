/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** server.c
*/

#include "server.h"
#include "client.h"
#include "client_handle.h"
#include "parse_args.h"
#include "response.h"
#include <stdlib.h>

int create_server_socket(int port)
{
    int s_socket;
    struct sockaddr_in server_addr;

    s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s_socket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(s_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("ERROR on binding");
        exit(2);
    }
    return s_socket;
}

void handle_communication(server_t *server, int current_fd)
{
    int new_fd;

    if (current_fd == server->socket) {
        new_fd = accept(server->socket, NULL, NULL);
        server->clients[new_fd] = init_client(new_fd);
        FD_SET(new_fd, &server->master);
        if (new_fd > server->max_fd)
            server->max_fd = new_fd;
        printf("[LOG] client %d connected\n", new_fd);
        send_response(server->clients[new_fd], "WELCOME\r\n");
    } else {
        if (!handle_client(server->clients[current_fd], server)) {
            free(server->clients[current_fd]);
            close(current_fd);
            FD_CLR(current_fd, &server->master);
            printf("[LOG] client %d disconnected\n", current_fd);
        }
    }
}

void manage_connection(server_t *server)
{
    server->temp = server->master;
    if (select(server->max_fd + 1, &server->temp, NULL, NULL,
            &server->timeval) < 0) {
        perror("error: select");
        exit(84);
    }
    for (int current_fd = 0; current_fd <= server->max_fd; current_fd++) {
        if (FD_ISSET(current_fd, &server->temp))
            handle_communication(server, current_fd);
    }
}

server_t *init_server(parse_args_t *args)
{
    server_t *server = malloc(sizeof(server_t));

    srand(time(NULL));
    server->socket = create_server_socket(args->port);
    server->max_fd = server->socket;
    server->current_fd = 0;
    server->clients = malloc(sizeof(client_t *) * MAX_CLIENTS);
    server->bin_args = args;
    server->teams = init_teams(args);
    server->map = init_map(args->width, args->height);
    server->ressourcesMax =
        calculate_required_ressources(args->width, args->height);
    server->ressource_clock = time(NULL);
    server->commands = NULL;
    server->timeval.tv_sec = 0;
    server->timeval.tv_usec = 100;
    FD_ZERO(&server->master);
    FD_SET(server->socket, &server->master);
    return server;
}

void start_server(parse_args_t *args)
{
    server_t *server = init_server(args);
    int first_call = 0;

    update_resources(server, 1);
    listen(server->socket, 5);
    printf("[LOG] server started on port: %d\n", args->port);
    display_args(args);
    while (1) {
        update_resources(server, 0);
        manage_connection(server);
        handle_commands(server);
        update_engine_food(server, first_call);
        first_call = 1;
    }
    free(server);
}
