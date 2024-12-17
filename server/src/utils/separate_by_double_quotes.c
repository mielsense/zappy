/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-sami.benkirane-saadi
** File description:
** separate_by_double_quotes.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_double_quotes(const char *s)
{
    for (int i = 0; s[i]; i++) {
        if (s[i] == '"')
            return 1;
    }
    return 0;
}

int string_is_valid(const char *s)
{
    int double_quotes = 0;

    if (!contains_double_quotes(s))
        return 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '"')
            double_quotes++;
    }
    if (double_quotes % 2 != 0)
        return 0;
    return 1;
}

char **add_in_parts(char **parts, const char *start, int length, int *count)
{
    parts = (char **)realloc(parts, (*count + 2) * sizeof(char *));
    parts[*count] = (char *)malloc((length + 1) * sizeof(char));
    strncpy(parts[*count], start, length);
    parts[*count][length] = '\0';
    (*count)++;
    return parts;
}

char **separate_by_double_quotes(const char *s)
{
    int inside_quotes = 0;
    const char *start = s;
    int count = 0;
    char **parts = NULL;
    int length = 0;

    if (!string_is_valid(s))
        return NULL;
    for (const char *p = s; *p; p++) {
        if (*p != '"')
            continue;
        if (inside_quotes) {
            length = p - start;
            parts = add_in_parts(parts, start, length, &count);
        } else
            start = p + 1;
        inside_quotes = !inside_quotes;
    }
    parts[count] = NULL;
    return parts;
}
