/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** normalize.c
*/

#include <stdlib.h>

int normalize(int value)
{
    if (value != 0)
        return value / abs(value);
    return 0;
}
