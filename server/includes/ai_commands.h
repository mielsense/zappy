/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ia_commands
*/

#pragma once
#include "commands.h"
#include "server.h"

void add_timed_command(server_t *server, char *command, double duration);
void look_right(client_t *client, server_t *server);
void look_left(client_t *client, server_t *server);
void look_top(client_t *client, server_t *server);
void look_bottom(client_t *client, server_t *server);
char *tile_content(tile_t **map, server_t *server, int x, int y);
void look(command_data_t data, server_t *server);
void forward(command_data_t data, server_t *server);
void right(command_data_t data, server_t *server);
void left(command_data_t data, server_t *server);
void inventory(command_data_t data, server_t *server);
void broadcast(command_data_t data, server_t *server);
void take_food(command_data_t data, server_t *server);
void take_linemate(command_data_t data, server_t *server);
void take_deraumere(command_data_t data, server_t *server);
void take_sibur(command_data_t data, server_t *server);
void take_mendiane(command_data_t data, server_t *server);
void take_phiras(command_data_t data, server_t *server);
void take_thystame(command_data_t data, server_t *server);
void take(command_data_t data, server_t *server);
void set_food(command_data_t data, server_t *server);
void set_linemate(command_data_t data, server_t *server);
void set_deraumere(command_data_t data, server_t *server);
void set_sibur(command_data_t data, server_t *server);
void set_mendiane(command_data_t data, server_t *server);
void set_phiras(command_data_t data, server_t *server);
void set_thystame(command_data_t data, server_t *server);
void set(command_data_t data, server_t *server);
int check_incantation(command_data_t data, server_t *server);
void end_incantation(command_data_t data, server_t *server);
void start_incantation(command_data_t data, server_t *server);
void ai_fork(command_data_t data, server_t *server);
void ai_fork_finished(command_data_t data, server_t *server);
void connect_nbr(command_data_t data, server_t *server);
void eject(command_data_t data, server_t *server);
