/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** get_player_id.c
*/

#include <stdlib.h>

int get_player_id(const char *str)
{
    if (str == NULL || str[0] != '#')
        return -1;
    return atoi(str + 1);
}
