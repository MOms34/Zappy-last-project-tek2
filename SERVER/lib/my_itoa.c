/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL : Ubuntu]
** File description:
** my_itoa
*/

#include "lib.h"

char *my_itoa(int nb)
{
    int i = 0;
    int j = 0;
    char *str = malloc(sizeof(char) * 12);

    if (nb == 0)
        return ("0");
    if (nb < 0) {
        str[i] = '-';
        i++;
        nb = -nb;
    }
    for (; nb > 0; nb = nb / 10)
        str[i++] = nb % 10 + '0';
    str[i] = '\0';
    for (j = 0; j < i / 2; j++) {
        str[j] ^= str[i - j - 1];
        str[i - j - 1] ^= str[j];
        str[j] ^= str[i - j - 1];
    }
    return (str);
}

int  n_is_digit(const char* str, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

int str_is_digit(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]) && str[i] != '\n')
            return 0;
    return 1;
}
