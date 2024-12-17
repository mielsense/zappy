/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** utils.h
*/

#pragma once
#include <stdlib.h>

char **separate_by_double_quotes(const char *s);
int tablen(char **tab);
char **split(char *str, char separator);
int random_bit(void);
int player_count(void *server_ptr, int x, int y);
int get_player_id(const char *str);
int normalize(int value);
