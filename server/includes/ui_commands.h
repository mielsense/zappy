/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** ui_commands.h
*/

#pragma once
#include "server.h"

void bct(command_data_t data, server_t *server);
void mct(command_data_t data, server_t *server);
void msz(command_data_t data, server_t *server);
void tna(command_data_t data, server_t *server);
void ppo(command_data_t data, server_t *server);
void plv(command_data_t data, server_t *server);
void pin(command_data_t data, server_t *server);
void pnw(client_t *client, server_t *server);
void sgt(command_data_t data, server_t *server);
void sst(command_data_t data, server_t *server);
void pic(command_data_t data, server_t *server, int required_players, client_t **list);
void pdr(command_data_t data, server_t *server);
void pgt(command_data_t data, server_t *server);
