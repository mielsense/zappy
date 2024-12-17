/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** commands.c
*/

#include "commands.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>

node_t *create_node(command_data_t data)
{
    static int current_key = 0;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    if (!new_node) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    new_node->key = current_key;
    new_node->data = data;
    new_node->next = NULL;
    current_key++;
    return new_node;
}

void append_node(node_t **head, command_data_t data)
{
    node_t *new_node = create_node(data);
    node_t *temp;

    printf("[LOG] command %s added (d: %is)\n", data.name, data.duration);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void delete_node(node_t **head, int key)
{
    node_t *temp = *head;
    node_t *prev = NULL;

    if (temp != NULL && temp->key == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

bool execute_command(node_t *node, server_t *server)
{
    time_t current_time = time(NULL);
    float diff = difftime(current_time, node->data.cast_time);
    float required_time = node->data.duration / server->bin_args->freq;

    if (diff >= required_time) {
        printf("[LOG] executing command %s for #%i (td: %.2f)\n",
            node->data.name, node->data.client->socket, diff);
        node->data.handler(node->data, server);
        return true;
    }
    return false;
}

void handle_commands(void *server_ptr)
{
    server_t *server = (server_t *)server_ptr;
    node_t *temp;
    int client_commands[MAX_CLIENTS];

    for (int i = 0; i < MAX_CLIENTS; i++)
        client_commands[i] = -1;
    if (!server->commands)
        return;
    temp = server->commands;
    while (temp != NULL) {
        if (client_commands[temp->data.client->socket] == -1)
            client_commands[temp->data.client->socket] = temp->key;
        if (client_commands[temp->data.client->socket] == temp->key) {
            if (execute_command(temp, server)) {
                client_commands[temp->data.client->socket] = -1;
                delete_node(&server->commands, temp->key);
            }
        }
        temp = temp->next;
    }
}
