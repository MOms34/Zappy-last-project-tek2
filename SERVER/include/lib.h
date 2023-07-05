/*
** EPITECH PROJECT, 2023
** B-NWP-400-MPL-4-1-myteams-gabriel.robert [WSL: Ubuntu]
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    char *my_itoa(int nb);
    int n_is_digit(const char *str, size_t n);
    int str_is_digit(const char *str);
    char *my_strcat(char *dest, char *src);
    int array_len(char **array);
    char *clear_str(char *str, char car);
    char **my_str_to_word_array(char *str, char *car);

#endif /* !LIB_H_ */
