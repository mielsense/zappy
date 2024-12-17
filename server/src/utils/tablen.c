/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-sami.rolland
** File description:
** tablen.c
*/

int tablen(char **tab)
{
    int i = 0;

    if (!tab)
        return 0;
    for (; tab[i]; i++)
        ;
    return i;
}
