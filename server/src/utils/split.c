/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** split.c
*/

#include <stdlib.h>
#include <unistd.h>

int count_separators(char *str, char separator)
{
    int count = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] == separator || str[i] == '\t')
            count++;
        i++;
    }
    return count;
}

int count_to_next_sep(char *str, char separator, int i)
{
    int count = 0;

    while (str[i] != separator && str[i] != '\0' && str[i] != '\n' &&
           str[i] != '\t') {
        count++;
        i++;
    }
    return count;
}

char *get_word(char *str, char separator, int *i)
{
    int length = count_to_next_sep(str, separator, *i);
    char *word = malloc((length + 1) * sizeof(char));
    int j = 0;

    while (j < length) {
        word[j] = str[*i];
        j++;
        (*i)++;
    }
    word[j] = '\0';
    (*i)++;
    return word;
}

char **clean_split(char **words)
{
    int length = 0;
    char **new_words;
    int i = 0;
    int j = 0;

    while (words[i]) {
        if (words[i][0])
            length++;
        i++;
    }
    new_words = malloc((length + 1) * sizeof(char *));
    i = 0;
    while (words[i]) {
        if (words[i][0]) {
            new_words[j] = words[i];
            j++;
        }
        i++;
    }
    new_words[j] = 0;
    return new_words;
}

char **split(char *str, char separator)
{
    int sep_count = count_separators(str, separator);
    char **array = malloc((sep_count + 2) * sizeof(char *));
    int i = 0;
    int j = 0;

    while (j < sep_count + 1 && str[i]) {
        array[j] = get_word(str, separator, &i);
        j++;
    }
    array[j] = 0;
    return clean_split(array);
}
