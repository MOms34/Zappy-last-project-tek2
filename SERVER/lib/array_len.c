/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** array_len
*/

#include "lib.h"

int array_len(char **array)
{
    int i = 0;

    for (; array[i]; i++);
    return i;
}

char *clear_str(char *str, char car)
{
    int i = 0;
    int j = 0;
    char *new_str = malloc(sizeof(char) * strlen(str) + 1);

    for (; str[i] != '\0'; i++)
        if (str[i] != car) {
            new_str[j] = str[i];
            j++;
        }
    new_str[j] = '\0';
    return new_str;
}
