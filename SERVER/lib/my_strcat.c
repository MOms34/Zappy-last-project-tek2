/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** my_strcat
*/

#include "lib.h"

char *my_strcat(char *dest, char *src)
{
    int dest_len = strlen(dest);
    int src_len = strlen(src);
    char *result = malloc(sizeof(char) * (dest_len + src_len) + 1);
    int i = 0;

    while (i < (dest_len)) {
        result[i] = dest[i];
        i++;
    }
    for (int j = 0; i < (dest_len + src_len); j++) {
        result[i] = src[j];
        i++;
    }
    result[i] = '\0';
    return result;
}
