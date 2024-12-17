/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** client_handle.h
*/

#pragma once
#include "client.h"
#include "command_handler.h"
#include <time.h>

struct node {
    command_data_t data;
    int key;
    struct node *next;
};

typedef struct node node_t;

node_t *create_node(command_data_t data);
void append_node(node_t **head, command_data_t data);
