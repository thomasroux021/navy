/*
** EPITECH PROJECT, 2019
** parser.c
** File description:
** parser
*/

#include "my.h"

int char_file(char *str)
{
    int br = 0;

    for (int i = 0; str[i]; i += 1) {
        if (i % 8 == 0)
            (i / 8 + 2 != str[i] - 48) ? br = 1 : 0;
        if (i % 8 - 1 == 0 || i % 8 - 4 == 0)
            (str[i] != ':') ? br = 1 : 0;
        if (i % 8 - 2 == 0 || i % 8 - 5 == 0)
            (str[i] < 65 || str[i] > 72) ? br = 1 : 0;
        if (i % 8 - 3 == 0 || i % 8 - 6 == 0)
            (str[i] < 49 || str[i] > 56) ? br = 1 : 0;
        if (i % 8 - 7 == 0)
            (str[i] != '\n') ? br = 1 : 0;
        if (br)
            return (-1);
    }
    return (0);
}

int parser_file(char *file)
{
    int fd;
    int size = 0;
    char *str = malloc(sizeof(char) * 33);

    if (str == NULL)
        return (-1);
    fd = open(file, O_RDONLY);
    if ((size = read(fd, str, 33)) == -1)
        return (-1);
    str[size] = '\0';
    if (size < 31 || size > 32)
        return (-1);
    close(fd);
    return (char_file(str));
}
