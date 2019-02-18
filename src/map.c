/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** map
*/

#include "my.h"

char **vert_fill(char **map, int k, char *str)
{
    int i = str[3 + 8 * k] - 49 + 1;
    int j = str[2 + 8 * k] - 65;

    while (i != str[6 + 8 * k] - 49 + 1) {
        if (map[i][j] != '.')
            return (NULL);
        else
            map[i][j] = 2 + k + 48;
        i += 1;
    }
    return (map);
}

char **hori_fill(char **map, int k, char *str)
{
    int i = str[3 + 8 * k] - 49;
    int j = str[2 + 8 * k] - 65 + 1;

    while (j != str[5 + 8 * k] - 65 + 1) {
        if (map[i][j] != '.')
            return (NULL);
        else
            map[i][j] = 2 + k + 48;
        j += 1;
    }
    return (map);
}

char **vert_fill_inv(char **map, int k, char *str)
{
    int i = str[3 + 8 * k] - 49 - 1;
    int j = str[2 + 8 * k] - 65;

    while (i != str[6 + 8 * k] - 49 - 1) {
        if (map[i][j] != '.')
            return (NULL);
        else
            map[i][j] = 2 + k + 48;
        i -= 1;
    }
    return (map);
}

char **hori_fill_inv(char **map, int k, char *str)
{
    int i = str[3 + 8 * k] - 49;
    int j = str[2 + 8 * k] - 65 - 1;

    while (j != str[5 + 8 * k] - 65 - 1) {
        if (map[i][j] != '.')
            return (NULL);
        else
            map[i][j] = 2 + k + 48;
        j -= 1;
    }
    return (map);
}

char **fill_map(char **map, char *str)
{
    for (int i = 0; i < 4; i += 1) {
        if (map[str[3 + 8 * i] - 49][str[2 + 8 * i] - 65] != '.')
            return (NULL);
        else
            map[str[3 + 8 * i] - 49][str[2 + 8 * i] - 65] = 2 + i + 48;
        (str[3 + 8 * i] - str[6 + 8 * i] < 0 && str[2 + 8 * i] -
        str[5 + 8 * i] == 0) ? map = vert_fill(map, i, str) : 0;
        (str[3 + 8 * i] - str[6 + 8 * i] > 0 && str[2 + 8 * i] -
        str[5 + 8 * i] == 0) ? map = vert_fill_inv(map, i, str) : 0;
        (str[2 + 8 * i] - str[5 + 8 * i] < 0 && str[3 + 8 * i] -
        str[6 + 8 * i] == 0) ? map = hori_fill(map, i, str) : 0;
        (str[2 + 8 * i] - str[5 + 8 * i] > 0 && str[3 + 8 * i] -
        str[6 + 8 * i] == 0) ? map = hori_fill_inv(map, i, str) : 0;
        if (map == NULL)
            return (NULL);
    }
    if (len_boat(map) == -1)
        return (NULL);
    print_map(map);
    return (map);
}
