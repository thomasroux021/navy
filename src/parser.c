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

char *parser_file(char *file)
{
    int fd;
    int size = 0;
    char *str = malloc(sizeof(char) * 33);

    if (str == NULL)
        return (NULL);
    fd = open(file, O_RDONLY);
    if ((size = read(fd, str, 33)) == -1)
        return (NULL);
    str[size] = '\0';
    if (size < 31 || size > 32)
        return (NULL);
    close(fd);
    if (char_file(str))
        return (NULL);
    return (str);
}

char **create_map(void)
{
    char **map = malloc(sizeof(char *) * 9);
    char *line;
    int j;
    int i;

    if (map == NULL)
        return (NULL);
    for (i = 0; i < 8; i += 1) {
        if ((line = malloc(sizeof(char) * 9)) == NULL)
            return (NULL);
        for (j = 0; j < 8; j += 1)
            line[j] = '.';
        line[j] = '\0';
        map[i] = line;
    }
    map[i] = NULL;
    return (map);
}

int len_boat(char **map)
{
    int len = 0;

    for (int i = 0; map[i] != NULL; i += 1) {
        for (int j = 0; map[i][j] != '\0'; j += 1) {
            (map[i][j] == '2') ? len += 1000 : 0;
            (map[i][j] == '3') ? len += 100 : 0;
            (map[i][j] == '4') ? len += 10 : 0;
            (map[i][j] == '5') ? len += 1 : 0;
        }
    }
    if (len != 2345)
        return (-1);
    return (0);
}
